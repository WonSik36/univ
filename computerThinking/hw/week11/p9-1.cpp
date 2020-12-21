#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int N, T;
    cin >> N >> T;

    vector<long long> people;
    for(int i=0; i<N; i++) {
        int p, v;
        cin >> p >> v;

        people.push_back(((long long)v)*T+p);
    }


    int cnt = 1;
    long long max = people.back();
    for(vector<long long>::reverse_iterator rit = people.rbegin(); rit != people.rend(); rit++) {
        if((*rit) >= max)
            continue;

        max = (*rit);
        cnt++;
    }

    cout << cnt << endl;

    return 0;
}