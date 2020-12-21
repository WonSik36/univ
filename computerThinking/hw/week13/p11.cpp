#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>

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

void backtrack(int cur, deque<int>* dq, bool* visited);
int dfs(int cur, bool* visited);

int N;
vector<string> words;
vector<int> g[1000];
vector<int> conG[1000];
int in[1000] = {0,};
int out[1000] = {0,};

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

    // for(int i=0;i<N;i++){
    //     cout << words[i] << endl;
    // }

    /* Make Graph */
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(i == j)
                continue;


            if(words[i].back() == words[j].front()) {
                in[j]++;
                out[i]++;

                g[i].push_back(j);

                conG[i].push_back(j);
                conG[j].push_back(i);
            }
        }
    }

    // for(int i=0;i<N;i++){
    //     cout << "words[" << i << "]: ";
    //     for(int j=0;j<g[i].size();j++){
    //         cout << g[i][j] << " ";
    //     }
    //     cout<<endl;
    // }

    /* Check All Nodes Connected */
    bool* visited = new bool[N];
    for(int i=0;i<N;i++){
        visited[i] = false;
    }

    int count = dfs(0, visited);
    if(count != N) {
        cout << "0" << endl;
        delete[] visited;
        return 0;
    }
    
    /* Check Eulerian Path */
    cout << "check eucl" << endl;
    for(int i=0;i<N;i++){
        cout << in[i] << " ";
    }
    cout << endl;
    for(int i=0;i<N;i++){
        cout << out[i] << " ";
    }
    cout << endl;

    int sum = 0;
    for(int i=0;i<N;i++){
        cout << (in[i] - out[i]) << " ";

        sum += (in[i] - out[i]);
    }
    cout << endl;

    cout << "sum: " << sum << endl;

    sum %= 2;

    if(sum != 0) {
        cout << "0" << endl;
        delete[] visited;
        return 0;
    }


    // int minus_one_appeared_time = 0;
    // int one_appeared_time = 0;
    // for(int i=0;i<N;i++){
    //     int gap = in[i] - out[i];

    //     cout << gap << " ";

    //     if(gap == 0) {

    //     } else if(gap == -1) {
    //         minus_one_appeared_time++;
    //     } else if(gap == 1) {
    //         one_appeared_time++;
    //     } else {
    //         cout << "0" << endl;
    //         delete[] visited;
    //         return 0;
    //     }
    // }
    // cout << endl;

    // if((minus_one_appeared_time == 0) && (one_appeared_time == 0)) {

    // } else if((minus_one_appeared_time == 1) && (one_appeared_time == 1)) {

    // } else {
    //     cout << "0" << endl;
    //     delete[] visited;
    //     return 0;
    // }



    /* Backtracking */

    deque<int> dq;
    for(int i=0;i<N;i++){
        visited[i] = false;
    }

    for(int i=0;i<N;i++){
        dq.push_back(i);
        visited[i] = true;

        backtrack(i, &dq, visited);

        if(dq.size() == N) 
            break;

        visited[i] = false;
        dq.pop_back();
    }

    if(dq.size() == N) {
        for(int i=0;i<N;i++){
            int idx = dq.front();
            dq.pop_front();

            cout << words[idx] << endl;
        }
    } else {
        cout << "0" << endl;
    }

    delete[] visited;

    return 0;
}

void backtrack(int cur, deque<int>* dq, bool* visited) {
    if(dq->size() == N)
        return;

    vector<int> adj = g[cur];

    for(int i=0; i < adj.size(); i++){
        if(visited[adj[i]])
            continue;

        dq->push_back(adj[i]);
        visited[adj[i]] = true;

        backtrack(adj[i], dq, visited);

        if(dq->size() == N) 
            return;

        visited[adj[i]] = false;
        dq->pop_back();
    }
}

int dfs(int cur, bool* visited) {
    visited[cur] = true;

    int count = 1;
    vector<int> adj = conG[cur];

    for(int i=0; i < adj.size(); i++) {
        if(visited[adj[i]])
            continue;

        count += dfs(adj[i], visited);
    }

    return count;
}