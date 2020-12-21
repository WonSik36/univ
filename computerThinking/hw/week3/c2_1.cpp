#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class Pos {
public:
    int y;
    int x;
    int value;
    int altitude;

    Pos(int _y, int _x, int _value, int _altitude){
        y = _y;
        x = _x;
        value = _value;
        altitude = _altitude;
    }
};


void init();
long long dfs(int y, int x);
void sort(int start, int end, vector<Pos*> *dq);
void swap(int l, int r, vector<Pos*> *dq);

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

    vector<Pos*> v;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            v.push_back(new Pos(i,j,0,map[i][j]));
        }
    }

    sort(0, N*N-1, &v);

    long long max = 0;
    for(int i=0;i<N*N;i++){
        int y = (*v[i]).y;
        int x = (*v[i]).x;

        long long res = dfs(y, x);
        max = max > res ? max : res;
    }

    cout << max;

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
    cout<<"y: "<<y<<" ,x: "<<x<<endl;
    if(memo[y][x] != -1){
        cout<<"using memo"<<endl;
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

    cout<<"result: "<<max<<endl;
    return memo[y][x] = max;
} 

void sort(int start, int end, vector<Pos*> *v){
    // cout<<"start: "<<start<<", end: "<<end<<endl;
    if(end-start == 0)
        return;

    Pos pivot = *(*v)[end];

    int l = start, r = end;
    while(l < r){
        // cout<<"l: "<<l<<", r: "<<r<<endl;
        while((*(*v)[l]).altitude < pivot.altitude && l<r){
            l++;
        }

        while((*(*v)[r]).altitude >= pivot.altitude && l<r){
            r--;
        }

        if(l != r)
            swap(l,r,v);
    }
    if(l != end)
        swap(l,end,v);

    if(start < l)
        sort(start, l-1, v);

    if(r < end)
        sort(r+1, end, v);
}

void swap(int l, int r, vector<Pos*> *v){
    Pos* tmp = (*v)[l];
    (*v)[l] = (*v)[r];
    (*v)[r] = tmp;
}