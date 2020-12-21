#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<pair<int, int>> applicants;
    for(int i=0;i<N;i++) {
        int x, y;
        cin >> x >> y;

        applicants.push_back(make_pair(x,y));
    }

    int max = 0;
    for(int i=0;i<N;i++){
        int cnt = 0;
        for(int j=0;j<N;j++){
            if(i==j)
                continue;

            // cout << "compare (" << applicants[i].first <<", "<<applicants[i].second<<") ";
            // cout << "(" << applicants[j].first <<", "<<applicants[j].second<<") " << endl;

            if(applicants[i].first > applicants[j].first && applicants[i].second < applicants[j].second) {
                cnt++;
            } else if(applicants[i].first < applicants[j].first && applicants[i].second > applicants[j].second) {
                cnt++;
            }
        }

        max = max > cnt ? max : cnt;
    }

    cout << max <<endl;
}
