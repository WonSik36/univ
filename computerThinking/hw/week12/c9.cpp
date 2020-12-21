#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int find(int node, int* parent);
void merge(int root1, int root2, int* parent);

int main() {
    int N;
    cin >> N;

    vector<pair<int, int>> applicants;
    applicants.push_back(make_pair(0,0));
    for(int i=0;i<N;i++) {
        int x, y;
        cin >> x >> y;

        applicants.push_back(make_pair(x,y));
    }

    int * parent = new int[N+1];
    for(int i=0;i<=N;i++){
        parent[i] = i;
    }

    int cnt = N;
    for(int i=1;i<N;i++){
        for(int j=i+1;j<=N;j++){
            int root1 = find(i, parent);
            int root2 = find(j, parent);

            // cout << "node[" << i <<"]: "<<root1;
            // cout << ", node[" << j <<"]: "<<root2;
            // cout << endl;

            if(root1 == root2)
                continue;

            if(applicants[i].first < applicants[j].first && applicants[i].second > applicants[j].second) {
                merge(root1, root2, parent);
                cnt--;
            }

            else if(applicants[i].first > applicants[j].first && applicants[i].second < applicants[j].second) {
                merge(root1, root2, parent);
                cnt--;
            }
        }
    }

    // for(int i=1;i<=N;i++) {
    //     cout << parent[i] << " ";
    // }
    // cout << endl;

    cout << cnt <<endl;

    delete[] parent;
}

int find(int node, int* parent) {
    if(node == parent[node]) {
        return node;
    }

    return parent[node] = find(parent[node], parent);
}

void merge(int root1, int root2, int* parent) {
    if(root1 > root2) {
        int tmp = root1;
        root1 = root2;
        root2 = tmp;
    }

    parent[root2] = root1;
}