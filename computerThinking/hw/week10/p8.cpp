#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool is_available(int k, int N, int D, vector<int> * tasks);

int main() {
    int N, D, M;
    cin >> N >> D >> M;

    priority_queue<int> pq;
    for(int i=0;i<M;i++){
        int t;
        cin >> t;

        pq.push((-1)*t);
    }

    vector<int> tasks;
    for(int i=0;i<M;i++){
        tasks.push_back((-1)*pq.top());
        pq.pop();
    }

    int l = 0, r = M+1;
    while(l+1 < r) {
        int mid = (l+r) / 2;

        if(is_available(mid, N, D, &tasks)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << r << endl;

    return 0;
}

bool is_available(int k, int N, int D, vector<int> * tasks) {
    vector<int>::iterator it = (*tasks).begin();

    for(int day=1; day<=N && it != (*tasks).end(); day++) {
        for(int i=0; i < k && it != (*tasks).end(); i++) {
            if(day > (*it)+D) 
                return false;

            if(day >= (*it))
                it++;
            else
                break;
        }
    }


    return true;
}