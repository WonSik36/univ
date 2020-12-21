#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void makeMaxFunc();
void printFunc(vector<pair<int,int>>* f);

const int MOD = 10007;

int N, M;
int p, q;
vector<pair<int,int>> f;
vector<pair<int,int>> g;
vector<pair<int,int>> maxF;

int main(){
    cin >> N;
    for(int i=0;i<N;i++){
        int x,y;
        cin >> x >> y;
        f.push_back(make_pair(x,y));
    }

    cin >> M;
    for(int i=0;i<M;i++){
        int x,y;
        cin >> x >> y;
        g.push_back(make_pair(x,y));
    }

    int p,q;
    cin >> p >> q;

    makeMaxFunc();
    // printFunc(&maxF);

    int sum = 0;
    for(vector<pair<int,int>>::iterator cur = maxF.begin(), next = cur+1; next != maxF.end(); cur++, next++){
        if((*next).first <= p || q < (*cur).first)
            continue;

        if((*cur).first <= p && q < (*next).first){
            // cout << "0.sum += " << (((long long)((q - p + 1) % MOD) * (*cur).second) % MOD) << endl;
            sum += (((long long)((q - p + 1) % MOD) * (*cur).second) % MOD);
        }else if((*cur).first <= p && p < (*next).first){
            // cout << "1.sum += " << (((long long)(((*next).first - p) % MOD) * (*cur).second) % MOD) << endl;
            sum += (((long long)(((*next).first - p) % MOD) * (*cur).second) % MOD);
        }else if((*cur).first <= q && q < (*next).first){
            // cout << "2.sum += " << (((long long)((q - (*cur).first + 1) % MOD) * (*cur).second) % MOD) << endl;
            sum += (((long long)((q - (*cur).first + 1) % MOD) * (*cur).second) % MOD);
        }else{
            // cout << "3.sum += " << (((long long)(((*next).first - (*cur).first) % MOD) * (*cur).second) % MOD) << endl;
            sum += (((long long)(((*next).first - (*cur).first) % MOD) * (*cur).second) % MOD);
        }

        sum %= MOD;
    }

    if(maxF.back().first <= q){
        if(maxF.back().first <= p){
            // cout << "4.sum += " << ((((q - p + 1) % MOD) * (long long)maxF.back().second) % MOD) << endl;
            sum += ((((q - p + 1) % MOD) * (long long)maxF.back().second) % MOD);
            sum %= MOD;
        }else{
            // cout << "4.sum += " << ((((q - maxF.back().first + 1) % MOD) * (long long)maxF.back().second) % MOD) << endl;
            sum += ((((q - maxF.back().first + 1) % MOD) * (long long)maxF.back().second) % MOD);
            sum %= MOD;
        }
    }

    cout << sum << endl;

    return 0;
}

void makeMaxFunc(){
    vector<pair<int,int>>::iterator it_f = f.begin();
    vector<pair<int,int>>::iterator it_g = g.begin();

    int curX = -2000000001;
    int curY = 0;
    while(it_f != f.end() && it_g != g.end()) {
        int nextX, nextY;

        if((*it_f).first < (*it_g).first){
            nextX = (*it_f).first;
            nextY = (*it_f).second;
            it_f++;
        }else if((*it_f).first > (*it_g).first){
            nextX = (*it_g).first;
            nextY = (*it_g).second;
            it_g++;
        }else{
            nextX = (*it_f).first;
            if((*it_f).second > (*it_g).second){
                nextY = (*it_f).second;
                it_f++;
            }else{
                nextY = (*it_g).second;
                it_g++;
            }
        }

        if(curX < nextX && curY < nextY){
            maxF.push_back(make_pair(nextX, nextY));
            curX = nextX;
            curY = nextY;
        }
    }

    while(it_f != f.end()){
        if(maxF.back().second < (*it_f).second)
            maxF.push_back((*it_f));
        it_f++;
    }

    while(it_g != g.end()){
        if(maxF.back().second < (*it_g).second)
            maxF.push_back((*it_g));
        it_g++;
    }
}

void printFunc(vector<pair<int,int>>* f){
    for(vector<pair<int,int>>::iterator it = (*f).begin(); it != (*f).end(); it++){
        cout << (*it).first << " " << (*it).second << endl;
    }
    cout<<endl;
}