#include <iostream>

using namespace std;

int adj_broken_count(int brokenCount);

int cnt = 0;

int main(){
    int count;
    cin >> count; 

    int realCount = 0;
    int brokenCount = 0;
    while(brokenCount != count){
        realCount++;
        brokenCount++;
        cnt++;

        if(brokenCount%10 == 4 || brokenCount%10 == 0)
            brokenCount = adj_broken_count(brokenCount);
    }

    cout << realCount << endl;

    return 0;
}

int adj_broken_count(int brokenCount){
    int count = brokenCount;
    int digit = 1;

    bool is4InCount = false; 

    while(count > 0){
        cnt++;
        if(count % 10 == 4){
            is4InCount = true;
            break;                    
        }

        count /= 10;
        digit *= 10;
    }

    if(is4InCount){
        return brokenCount+digit;
    }else{
        return brokenCount;
    }
}