#include <iostream>

using namespace std;

int get_root(int a);
void merge(int a, int b);
bool is_same_node(int a, int b);

int root[10001];
int main() {
    int N, M;
    cin >> N;
    cin >> M;    

    for(int i=1;i<=N;i++){
        root[i] = i*2 - 1;
    }

    int res = -1;
    for(int i=1;i<=M;i++){
        // for(int i=1;i<=N;i++){
        //     cout << root[i] << " ";
        // }
        // cout << endl;

        int a, b;
        cin >> a >> b;

        if(res != -1)
            continue;

        int root_a = get_root(a);
        int root_b = get_root(b);

        // cout << "root_a: " << root_a << endl;
        // cout << "root_b: " << root_b << endl << endl;

        if(is_same_node(root_a, root_b)){
            if(root_a == root_b)
                res = i;
            continue;
        }

        if(root_a < root_b) {
            merge(root_a, root_b);
        } else {
            merge(root_b, root_a);
        }
    }

    cout << res << endl;

    return 0;
}

int get_root(int a) {
    if(root[a] == a*2-1) {
        return root[a];
    }

    int r = get_root((root[a]+1) / 2);

    if(is_same_node(r, root[a]))
        return root[a];
    
    if(root[a] % 2 == 0) {
        root[a] = r % 2 == 1 ? r+1 : r-1;
    } else {
        root[a] = r;
    }

    return root[a];
}

void merge(int a, int b) {
    if(a % 2 == b % 2) {
        root[(b+1)/2] = a % 2 == 1 ? a+1 : a;
    } else {
        root[(b+1)/2] = a % 2 == 1 ? a : a-1;
    }
}

bool is_same_node(int a, int b) {
    return (a+1)/2 == (b+1)/2;
}