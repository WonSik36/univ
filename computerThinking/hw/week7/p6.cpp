#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

void assemble_puzzle(int cur);
bool is_valid_pos(int dy, int dx, vector<pair<int, int>>* puzzle);
void init_map();
void print_map();
void delete_map();

int N;
int length;
int ** map;
bool is_done;
vector<vector<pair<int, int>>> puzzles;
int main(){
    int total_blocks = 0;

    cin >> N;
    for(int i=0; i<N; i++){
        int row, col;
        cin >> row >> col;

        vector<pair<int, int>> puzzle;

        for(int y=0; y<row; y++){
            for(int x=0; x<col; x++){
                int block;
                cin >> block;

                if(block == 1){
                    puzzle.push_back(make_pair(y, x));
                    total_blocks++;
                }
            }
        }

        puzzles.push_back(puzzle);
    }


    length = sqrt(total_blocks);

    init_map();

    is_done = false;
    assemble_puzzle(0);

    if(is_done){
        print_map();
    } else {
        cout << "No solution possible" << endl;
    }

    delete_map();
    // for(int i=0;i<N;i++){
    //     int y, x;

    //     for(int j=0; j<puzzles[i].size(); j++){
    //         y = puzzles[i][j].first;
    //         x = puzzles[i][j].second;

    //         cout << y <<" "<<x<<endl;
    //     }
    //     cout<<endl;
    // }

    return 0;
}

void assemble_puzzle(int cur) {
    if(is_done)
        return;

    if(cur == N){
        is_done = true;
        return;
    }

    for(int y=0; y < length; y++){
        for(int x=0; x < length; x++){
            if(!is_valid_pos(y, x, &puzzles[cur]))
                continue;

            for(int idx=0; idx < puzzles[cur].size(); idx++){
                int ny = y + puzzles[cur][idx].first;
                int nx = x + puzzles[cur][idx].second;
                map[ny][nx] = cur+1;
            }

            assemble_puzzle(cur+1);
            if(is_done)
                return;

            for(int idx=0; idx < puzzles[cur].size(); idx++){
                int ny = y + puzzles[cur][idx].first;
                int nx = x + puzzles[cur][idx].second;
                map[ny][nx] = 0;
            }
        }
    }
}

bool is_valid_pos(int dy, int dx, vector<pair<int, int>>* puzzle) {
    for(int idx=0; idx < (*puzzle).size(); idx++) {
        int ny = dy + (*puzzle)[idx].first;
        int nx = dx + (*puzzle)[idx].second;

        if(ny < 0 || ny >= length || nx < 0 || nx >= length)
            return false;

        if(map[ny][nx] != 0)
            return false;
    }

    return true;
}

void init_map() {
    map = new int*[length];
    for(int i = 0; i < length; ++i)
        map[i] = new int[length];

    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            map[i][j] = 0;
        }
    }
}

void print_map() {
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            cout << map[i][j] << " ";
        }
        cout <<endl;
    }
}

void delete_map() {
    for(int i=0; i < length; i++)
        delete[] map[i];
    delete[] map;
}