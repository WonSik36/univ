#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void sort(int start, int end, vector<pair<int,int>> *v);

int main(){
    int N, K;
    cin >> N >> K;
    K *= 2;

    vector<pair<int,int>> buildings;
    for(int i=0;i<N;i++){
        int g, x;
        cin >> g >> x;
        buildings.push_back(make_pair(x,g));
    }

    sort(0, N-1, &buildings);

    for(int i=0;i<buildings.size();i++){
        // cout << buildings[i].first << " " << buildings[i].second<<endl;
    }

    int l = 0, r = 0;
    int posL = buildings[0].first, posR = buildings[0].first;
    int dist = 0;
    long long sum = buildings[0].second;
    long long maxSum = sum;
    while(true){
        // cout << "l: "<<l<<" r: "<<r<<" dist: "<<dist<<" sum: "<<sum<<endl;
        if(dist >= K){
            sum -= buildings[l].second;
            l++;
            posL = buildings[l].first;
        }else if(r == N-1){
            break;
        }else{
            r++;
            sum += buildings[r].second;
            posR = buildings[r].first;
        }

        dist = posR - posL;
        if(dist <= K)
            maxSum = maxSum > sum ? maxSum: sum;
    }

    cout << maxSum << endl;

    return 0;
}

void sort(int start, int end, vector<pair<int,int>> *v){
    // cout<<"start: "<<start<<", end: "<<end<<endl;
    if(end-start == 0)
        return;

    pair<int,int> pivot = (*v)[end];

    int l = start, r = end;
    while(l < r){
        // cout<<"l: "<<l<<", r: "<<r<<endl;
        while((*v)[l].first < pivot.first && l<r){
            l++;
        }

        while((*v)[r].first >= pivot.first && l<r){
            r--;
        }

        if(l != r)
            (*v)[l].swap((*v)[r]);
    }
    if(l != end)
        (*v)[l].swap((*v)[end]);

    if(start < l)
        sort(start, l-1, v);

    if(r < end)
        sort(r+1, end, v);
}

