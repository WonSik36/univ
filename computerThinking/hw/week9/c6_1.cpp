#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> cards;
    for(int i=0;i<N;i++){
        int card;
        cin >> card;
        cards.push_back(card);
    }
    
    int * asc_len = new int[N];
    for(int i=0;i<N;i++){
        asc_len[i] = 1;
    }
    int * desc_len = new int[N];
    for(int i=0;i<N;i++){
        desc_len[i] = 1;
    }
    
    for(int i=0; i < N; i++){
        for(int j=i-1; j >= 0; j--) {
            if(cards[i] > cards[j])
                asc_len[i] = asc_len[i] > asc_len[j]+1 ? asc_len[i] : asc_len[j]+1;
        }
    }

    for(int i=N-1; i >= 0; i--){
        for(int j=i+1; j < N; j++) {
            if(cards[i] > cards[j])
                desc_len[i] = desc_len[i] > desc_len[j]+1 ? desc_len[i] : desc_len[j]+1;
        }
    }
    
    int max = 0;
    for(int i=0;i<N;i++){
        int score = asc_len[i] + desc_len[i] - 1;
        max = max > score ? max : score;
    }

    cout << max << endl;

    delete[] asc_len;
    delete[] desc_len;
    return 0;
}