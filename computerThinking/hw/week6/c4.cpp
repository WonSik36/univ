#include <iostream>
#include <queue>

using namespace std;

int calc_using_poles(int gap);

int N, K;
vector<int> poles;
int main(){
    cin >> N >> K;

    priority_queue<int> pq;
    for(int i=0;i<N;i++){
        int pole;
        cin >> pole;
        pq.push((-1)*pole);
    }

    while(!pq.empty()){
        poles.push_back((-1)*pq.top());
        pq.pop();
    }


    int lo = 0, hi = poles.back() - poles.front() + 1;
    while(lo+1 < hi){
        int mid = (lo+hi) >> 1;

        if(calc_using_poles(mid) >= K){
            lo = mid;
        }else{
            hi = mid;
        }
    }

    int min_dist = lo;

    cout << min_dist << endl;

    return 0;
}

int calc_using_poles(int gap){
    int using_poles = 1;

    for(vector<int>::iterator it = poles.begin()+1, cur = poles.begin(); it != poles.end(); it++){
        if((*it) - (*cur) >= gap){
            using_poles++;
            cur = it;
        }
    }

    return using_poles;
}