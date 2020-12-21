#include <iostream>
#include <vector>

using namespace std;

int lower_bound(vector<int>* lis, int card);

int main() {
    int N;
    cin >> N;

    vector<int> cards;
    vector<int> cards_reverse;
    for(int i=0;i<N;i++){
        int card;
        cin >> card;
        cards.push_back(card);
        cards_reverse.insert(cards_reverse.begin(), card);
    }

    vector<int> asc_lis;
    vector<int> asc_idx;
    for(int i=0;i<N;i++){
        int idx = lower_bound(&asc_lis, cards[i]);
        if(idx == asc_lis.size())
            asc_lis.push_back(cards[i]);
        else
            asc_lis[idx] = cards[i];
        asc_idx.push_back(idx);
    }

    vector<int> desc_lis;
    vector<int> desc_idx;
    for(int i=0;i<N;i++){
        int idx = lower_bound(&desc_lis, cards_reverse[i]);
        if(idx == desc_lis.size())
            desc_lis.push_back(cards_reverse[i]);
        else
            desc_lis[idx] = cards_reverse[i];
        desc_idx.insert(desc_idx.begin(), idx);
    }

    // for(int i=0;i<N;i++){
    //     cout << asc_idx[i] << " ";
    // }
    // cout << endl;
    // for(int i=0;i<N;i++){
    //     cout << desc_idx[i] << " ";
    // }
    // cout << endl;

    int max = 0;
    for(int i=0;i<N;i++){
        int score = asc_idx[i] + desc_idx[i] + 1;
        max = max > score ? max : score;
    }

    cout << max << endl;

    return 0;
}

int lower_bound(vector<int>* lis, int card) {
    if((*lis).empty())
        return 0;

    int l = -1, r = (*lis).size();
    while(l+1 < r) {
        int mid = (l+r) >> 1;

        if((*lis)[mid] < card) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return r;
}