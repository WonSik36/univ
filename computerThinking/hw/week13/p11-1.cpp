#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <utility>

using namespace std;


class Compare {
public:
    bool operator() (string l, string r) {
        if(l > r)
            return true;
        else
            return false;
    }
};

int dfs_con(int cur, bool* visited);
void dfs_eul(int cur, bool* visited, deque<string>* dq);

int N;
vector<string> words;
vector<pair<int,pair<string,int>>> g[26];
vector<int> con_g[1000];
int in[26] = {0,};
int out[26] = {0,};

int main() {
    cin >> N;

    priority_queue<string, vector<string>, Compare> pq;
    for(int i=0;i<N;i++) {
        string word;
        cin >> word;

        pq.push(word);
    }

    /* Sorting */
    for(int i=0;i<N;i++) {
        string word = pq.top();
        pq.pop();

        words.push_back(word);
    }

    /* Make Edge based Graph */
    for(int i=0;i<N;i++) {
        int first = words[i].front() - 'a';
        int last = words[i].back() - 'a';

        g[first].push_back(make_pair(last, make_pair(words[i], i)));

        out[first]++;
        in[last]++;
    }

    // for(int i=0;i<26;i++){
    //     cout << "g[" << i << "]: ";
    //     for(int j=0;j<g[i].size();j++){
    //         cout << g[i][j].second.first << " ";
    //     }
    //     cout<<endl;
    // }

    /* Make Node based Graph */
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(i == j)
                continue;

            int last = words[i].back() - 'a';
            int first = words[j].front() - 'a';

            if(last == first) {
                con_g[i].push_back(j);
                con_g[j].push_back(i);
            }
        }
    }

    /* check Connected Graph */
    bool* visited = new bool[N];
    for(int i=0;i<N;i++){
        visited[i] = false;
    }

    int count = dfs_con(0, visited);
    if(count != N) {
        cout << "0" << endl;
        delete[] visited;
        return 0;
    }

    // cout<<"in"<<endl;
    // for(int i=0;i<26;i++) {
    //     cout << in[i] << " ";
    // }
    // cout << endl;
    // cout<<"out"<<endl;
    // for(int i=0;i<26;i++) {
    //     cout << out[i] << " ";
    // }
    // cout << endl;

    /* Check Eulerian Path */
    int num_of_zero = 0;
    int num_of_one = 0;
    int num_of_minus_one = 0;
    int start = -1;
    for(int i=0;i<26;i++) {
        int degree = in[i] - out[i];

        if(degree == 0)
            num_of_zero++;
        else if(degree == 1)
            num_of_one++;
        else if(degree == -1) {
            num_of_minus_one++;
            start = i;
        }
    }

    if(num_of_zero + num_of_one + num_of_minus_one != 26) {
        cout << "0" << endl;
        delete[] visited;
        return 0;
    }

    if(num_of_zero != 26) {
        if(num_of_one == 1 && num_of_minus_one == 1) {

        } else {
            cout << "0" << endl;
            delete[] visited;
            return 0;
        }
    }


    /* Find Eulerian Path or Circuit */
    for(int i=0;i<N;i++){
        visited[i] = false;
    }
    deque<string> dq;

    if(start != -1) {
        // eulerian path
        dfs_eul(start, visited, &dq);
    } else {
        // eulerian circuit
        int first = words[0].front() - 'a';
        dfs_eul(first, visited, &dq);
    }

    while(!dq.empty()) {
        string word = dq.front();
        dq.pop_front();

        cout << word << endl;
    }

    delete[] visited;

    return 0;
}

int dfs_con(int cur, bool* visited) {
    visited[cur] = true;

    int count = 1;
    vector<int> adj = con_g[cur];

    for(int i=0; i < adj.size(); i++) {
        if(visited[adj[i]])
            continue;

        count += dfs_con(adj[i], visited);
    }

    return count;
}

void dfs_eul(int cur, bool* visited, deque<string>* dq) {
    if(dq->size() == N)
        return;

    vector<pair<int,pair<string,int>>> adj = g[cur];
    for(int i=0;i<adj.size();i++) {
        int next = adj[i].first;
        string word = adj[i].second.first;
        int edge_num = adj[i].second.second;

        if(visited[edge_num])
            continue;
        visited[edge_num] = true;
        dq->push_back(word);

        dfs_eul(next, visited, dq);
        if(dq->size() == N)
            return;

        dq->pop_back();
        visited[edge_num] = false;
    }
}