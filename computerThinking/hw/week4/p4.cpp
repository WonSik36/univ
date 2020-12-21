#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

long long hanoi(int cur, int from, int through, int to, vector<vector<int>>* state);
long long power(int x, int y);

int N, K;
int main(){
    cin >> N >> K;
    K--;

    vector<vector<int>> input(3);
    for(int i=0;i<3;i++){
        int numberOfDisk;
        cin >> numberOfDisk;
        for(int j=0;j<numberOfDisk;j++){
            int disk;
            cin >> disk;
            input[i].push_back(disk);
        }
    }

    int cur = N;
    while(input[K].size() > 0 && input[K].front() == cur){
        input[K].erase(input[K].begin());
        cur--;
    }

    long long cnt = 0;
    if(cur != 0){
        int to = K;
        int from = (to+1) % 3;
        int through = (to+2) % 3;

        if(input[through].size() > 0 && input[through].front() == cur){
            from = (to+2) % 3;
            through = (to+1) % 3;
        }

        cnt = hanoi(cur, from, through, to, &input);
    }

    cout << cnt << endl;
    return 0;
}

long long hanoi(int cur, int from, int through, int to, vector<vector<int>>* state) {
    if(cur == 1){
        (*state)[to].push_back((*state)[from].front());
        (*state)[from].erase((*state)[from].begin());

        return 1;
    }

    long long cnt = 0;
    
    if((*state)[through].size() < cur-1){
        (*state)[from].erase((*state)[from].begin());

        int next = cur-1;
        while((*state)[through].size() > 0 && (*state)[through].front() == next){
            (*state)[through].erase((*state)[through].begin());
            next--;
        }

        int newTo = through;
        int newFrom = (newTo+1) % 3;
        int newThrough = (newTo+2) % 3;

        if((*state)[newThrough].size() > 0 && (*state)[newThrough].front() == next){
            newFrom = (newTo+2) % 3;
            newThrough = (newTo+1) % 3;
        }

        cnt += hanoi(next, newFrom, newThrough, newTo, state);

        for(; next < cur-1; next++){
            (*state)[through].insert((*state)[through].begin(), next+1);    
        }

        (*state)[from].insert((*state)[from].begin(), cur);
    }


    cnt++;
    (*state)[to].push_back((*state)[from].front());
    (*state)[from].erase((*state)[from].begin());

    cnt += (power(2, cur-1) - 1);
    for(int i=0, size = (*state)[through].size(); i < size; i++){
        (*state)[to].push_back((*state)[through].front());
        (*state)[through].erase((*state)[through].begin());
    }

    return cnt;
}

long long power(int x, int y){
    long long sum = 1;
    for(int i=0;i<y;i++){
        sum *= x;
    }

    return sum;
}