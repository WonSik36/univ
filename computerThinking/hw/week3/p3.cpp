#include <iostream>
#include <deque>

using namespace std;

void sort(int start, int end, deque<int> *dq);
void swap(int l, int r, deque<int> *dq);

int main(){
    int N = 0, M;
    cin >> M;

    deque<int> dq;
    while(true){
        int num;
        cin >> num;
        if(cin.eof())
            break;
        dq.push_back(num);
        N++;
    }

    sort(0, N-1, &dq);

    int cnt = 0;
    while(dq.size() > 1){
        int first = dq.front();
        int last = dq.back();

        if(first + last <= M){
            dq.pop_front();
            dq.pop_back();
            cnt++;
        }else{
            dq.pop_back();
            cnt++;
        }
    }

    if(dq.size() == 1)
        cnt++;

    cout << cnt << endl;

    return 0;
}

void sort(int start, int end, deque<int> *dq){
    // cout<<"start: "<<start<<", end: "<<end<<endl;
    if(end-start == 0)
        return;

    int pivot = (*dq)[end];

    int l = start, r = end;
    while(l < r){
        // cout<<"l: "<<l<<", r: "<<r<<endl;
        while((*dq)[l] < pivot && l<r){
            l++;
        }

        while((*dq)[r] >= pivot && l<r){
            r--;
        }

        if(l != r)
            swap(l,r,dq);
    }
    if(l != end)
        swap(l,end,dq);

    if(start < l)
        sort(start, l-1, dq);

    if(r < end)
        sort(r+1, end, dq);
}

void swap(int l, int r, deque<int> *dq){
    int tmp = (*dq)[l];
    (*dq)[l] = (*dq)[r];
    (*dq)[r] = tmp;
}