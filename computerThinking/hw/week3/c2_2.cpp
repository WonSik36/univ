#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

using namespace std;

void init();
long long dfs(int y, int x);

int map[500][500];
long long memo[500][500];
int N;
int dY[4] = {0, -1, 0, 1};
int dX[4] = {1, 0, -1, 0};

int main(){
    ifstream in("input.txt");

    // cin >> N;
    // for(int i=0;i<N;i++){
    //     for(int j=0;j<N;j++){
    //         cin >> map[i][j];
    //     }
    // }
    in >> N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            in >> map[i][j];
        }
    }

    init();

    vector<pair<int,pair<int,int>>> v;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            v.push_back(make_pair(map[i][j], make_pair(i,j)));
        }
    }

    sort(v.begin(), v.end());

    long long max = 0;
    for(int i=0;i<N*N;i++){
        int y = v[i].second.first;
        int x = v[i].second.second;
    
        long long res = dfs(y, x);
        max = max > res ? max : res;
    }

    cout << max << endl;

    return 0;
}

void init(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            memo[i][j] = -1;
        }
    }
}

long long dfs(int y, int x){
    // cout<<"y: "<<y<<", x: "<<x<<endl;
    if(memo[y][x] != -1){
        return memo[y][x];
    }

    long long max = 0;
    for(int i=0;i<4;i++){
        if(dY[i]+y >= 0 && dY[i]+y < N && dX[i]+x >= 0 && dX[i]+x < N){
            int newY = dY[i]+y;
            int newX = dX[i]+x;

            if(map[y][x] > map[newY][newX]){
                long long res = dfs(newY, newX) + map[y][x] - map[newY][newX];
                max = max > res ? max : res;
            }
        }
    }

    // cout<<"result: "<<max<<endl;
    return memo[y][x] = max;
} 