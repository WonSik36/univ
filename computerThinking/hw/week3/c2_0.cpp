#include <iostream>
#include <deque>

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
void sort(int start, int end, deque<Pos*> *dq);
void swap(int l, int r, deque<Pos*> *dq);

int map[500][500];
long long memo[500][500];
int N;
int dY[4] = {0, -1, 0, 1};
int dX[4] = {1, 0, -1, 0};

int main(){
    cin >> N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> map[i][j];
        }
    }

    init();

    deque<Pos*> dq;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            dq.push_back(new Pos(i,j,0,map[i][j]));
        }
    }

    sort(0, N*N-1, &dq);

    long long max = 0;
    while(!dq.empty()){
        Pos last = *(dq.back());
        dq.pop_back();

        memo[last.y][last.x] = last.value;

        max = max > last.value ? max : last.value;

        for(int i=0;i<4;i++){
            if(dY[i]+last.y >= 0 && dY[i]+last.y < N && dX[i]+last.x >= 0 && dX[i]+last.x < N){
                int newY = dY[i]+last.y;
                int newX = dX[i]+last.x;

                if(map[last.y][last.x] > map[newY][newX] && memo[newY][newX] < last.value + map[last.y][last.x] - map[newY][newX]){
                    dq.push_back(new Pos(newY, newX, last.value + map[last.y][last.x] - map[newY][newX], 0));
                }
            }
        }
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

void sort(int start, int end, deque<Pos*> *dq){
    // cout<<"start: "<<start<<", end: "<<end<<endl;
    if(end-start == 0)
        return;

    Pos pivot = *(*dq)[end];

    int l = start, r = end;
    while(l < r){
        // cout<<"l: "<<l<<", r: "<<r<<endl;
        while((*(*dq)[l]).altitude < pivot.altitude && l<r){
            l++;
        }

        while((*(*dq)[r]).altitude >= pivot.altitude && l<r){
            r--;
        }

        if(l != r)
            swap(l,r,dq);
    }
    if(l != end)
        swap(l,end,dq);

    if(start < l)
        sort(start, l-1, dq);

    if(r < end)
        sort(r+1, end, dq);
}

void swap(int l, int r, deque<Pos*> *dq){
    Pos* tmp = (*dq)[l];
    (*dq)[l] = (*dq)[r];
    (*dq)[r] = tmp;
}