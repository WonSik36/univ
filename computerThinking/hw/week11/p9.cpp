#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class CompareFirst{
public:
    bool operator() (pair<int, int> l, pair<int, int> r){
        if(l.first > r.first)
            return true;
        else
            return false;
    }
};
class CompareSecond{
public:
    bool operator() (pair<int, long long> l, pair<int, long long> r){
        if(l.second > r.second) {
            return true;

        } else if(l.second < r.second) {
            return false;
        } else {
            if(l.first > r.first) {
                return false;
            } else {
                return true;
            }
        }
    }
};

int main() {
    int N, T;
    cin >> N >> T;

    priority_queue<pair<int, long long>, vector<pair<int, long long>>, CompareSecond> pq_second;
    for(int i=0; i<N; i++) {
        int p, v;
        cin >> p >> v;

        pq_second.push(make_pair(p, ((long long)v)*T+p));
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareFirst> pq_first;

    pair<int, long long> prev = pq_second.top();
    pq_second.pop();
    pq_first.push(make_pair(prev.first, 0));
    for(int i=1, idx=1; i<N; i++) {
        pair<int, long long> pair = pq_second.top();
        pq_second.pop();

        if(pair.second == prev.second)
            continue;

        pq_first.push(make_pair(pair.first, idx++));
        prev = pair;
    }

    vector<int> people;
    while(!pq_first.empty()) {
        pair<int, int> pair = pq_first.top();
        pq_first.pop();

        people.push_back(pair.second);
    }

    int cnt = 0;
    int max = people.back();
    for(vector<int>::reverse_iterator rit = people.rbegin(); rit != people.rend(); rit++) {
        if((*rit) > max)
            continue;

        max = (*rit);
        cnt++;
    }

    cout << cnt << endl;

    return 0;
}