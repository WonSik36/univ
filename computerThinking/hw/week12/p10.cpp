#include <iostream>
#include <vector>

using namespace std;

void init_vessels();
void print_vessels();
void print_weights();
void copy_arr(bool* dst, bool* src);
void and_arr(bool* dst, bool* src);
void find_complete_graph(int cur, vector<int>* tumors, int weight, bool* available_tissues);

int N, B;
bool** vessels;
int* weights;
int max_weight = 0;

int main() {
    cin >> N >> B;

    weights = new int[N];
    vessels = new bool*[N];
    for(int i=0; i<N;i++){
        vessels[i] = new bool[N];
    }

    init_vessels();

    for(int i=0;i<N;i++){
        cin >> weights[i];
    }

    for(int i=0;i<B;i++){
        int start, end;
        cin >> start >> end;
        start--;
        end--;

        vessels[start][end] = true;
        vessels[end][start] = true;
    }

    // print_weights();
    // print_vessels();

    bool* available_tissues = new bool[N];
    vector<int> tumors;
    int weight = 0;
    for(int i=0;i<N-1;i++){
        tumors.push_back(i);
        weight = weights[i];
        copy_arr(available_tissues, vessels[i]);

        find_complete_graph(i, &tumors, weight, available_tissues);

        tumors.pop_back();
    }

    cout << max_weight << endl;

    delete[] available_tissues;
    for(int i=0; i<N; i++) {
        delete [] vessels[i];
    }
    delete[] vessels;
    delete[] weights;
}

void init_vessels() {
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            vessels[i][j] = false;
        }
    }
}

void print_vessels() {
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << vessels[i][j] << " ";
        }
        cout << endl;
    }
}

void print_weights() {
    for(int i=0;i<N;i++){
        cout << weights[i] << " ";
    }
    cout << endl;
}

void copy_arr(bool* dst, bool* src) {
    for(int i=0;i<N;i++){
        dst[i] = src[i];
    }
}

void and_arr(bool* dst, bool* src) {
    for(int i=0;i<N;i++){
        dst[i] &= src[i];
    }
}

void find_complete_graph(int cur, vector<int>* tumors, int weight, bool* available_tissues) {
    if(tumors->size() >= 2) {
        max_weight = max_weight > weight ? max_weight : weight;
    }

    bool* next_avail_tissues = new bool[N];
    for(int i=0;i<N;i++) {
        if(!available_tissues[i])
            continue;

        tumors->push_back(i);
        weight += weights[i];
        copy_arr(next_avail_tissues, available_tissues);
        and_arr(next_avail_tissues, vessels[i]);

        find_complete_graph(i, tumors, weight, next_avail_tissues);

        weight -= weights[i];
        tumors->pop_back();
    }

    delete[] next_avail_tissues;
}