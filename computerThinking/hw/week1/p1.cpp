#include <iostream>
#include <cmath>    // dont believe double
#include <time.h>

using namespace std;

int adj_broken_count(int brokenCount);

int cnt = 0;

int main(){
    int count;
    cin >> count; 

    clock_t start = clock();

    int realCount = 0;
    int brokenCount = 0;
    while(brokenCount != count){
        realCount++;
        brokenCount++;
        cnt++;

        if(brokenCount%10 == 4 || brokenCount%10 == 0)
            brokenCount = adj_broken_count(brokenCount);
    }

    clock_t end = clock();

    cout << realCount << endl;
    cout << "time: "<<  (double)(end - start)/CLOCKS_PER_SEC << endl;
    cout << "Count: "<<cnt<<endl;

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