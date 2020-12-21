#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const long long DUMMY = -1;
const long long INF = 9223372036854775807;

long long calc_min_time(int first, int last);

int sum[501];
long long min_time[500][500];

int main(){
    int N;
    cin >> N;

    vector<int> pieces;
    for(int i=0;i<N;i++){
        int piece;
        cin >> piece;
        pieces.push_back(piece);
    }

    memset(sum, 0, sizeof(sum[0]) * 501);
    for(int i=0;i<N;i++){
        sum[i+1] = pieces[i] + sum[i];
    }

    memset(min_time, DUMMY, sizeof(min_time[0][0]) * 500 * 500);
    for(int i=0;i<N;i++){
        min_time[i][i] = 0;
    }
    
    long long min = calc_min_time(0, N-1);

    cout << min << endl;

    return 0;
}

long long calc_min_time(int first, int last) {
    if(min_time[first][last] != -1) {
        return min_time[first][last];
    }

    long long min = INF;
    for(int i=first; i<last; i++){
        long long t = calc_min_time(first, i) + calc_min_time(i+1, last) + sum[last+1] - sum[first];
        min = min < t ? min : t;
    }

    return min_time[first][last] = min;
}