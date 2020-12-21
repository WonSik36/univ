#include <iostream>

using namespace std;

int main(){
    int N;
    unsigned long long memo[100001];
    cin >> N;

    memo[1] = 1;
    memo[2] = 1;
    memo[3] = 2;
    memo[4] = 4;

    for(int i=5;i<=100000;i++){
        memo[i] = memo[i-1] + memo[i-3] + memo[i-4];
    }

    cout << memo[N] << endl;
    return 0;
}