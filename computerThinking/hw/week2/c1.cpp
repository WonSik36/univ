#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void printList(vector<vector<int>> graph);
void printArr(int N, int arr[]);

int main(){
    int N, K ,E;
    cin >> N >> K >> E;

    vector<vector<int>> graph(2001);
    int numberOfEdge[2001] = {0};
    for(int i=0;i<E;i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);

        numberOfEdge[a]++;
        numberOfEdge[b]++;
    }

    // printList(graph);
    // printArr(N, numberOfEdge);
    
    queue<int> q;
    for(int i=1;i<=N;i++){
        if(numberOfEdge[i] < K)
            q.push(i);
    }

    int cnt = 0;
    bool visited[2001] = {false};
    while(!q.empty()){
        int first = q.front();
        q.pop();

        if(visited[first])
            continue;
        visited[first] = true;
        cnt++;

        vector<int> adj = graph[first];
        for(int i=0;i<adj.size();i++){
            numberOfEdge[adj[i]]--;

            if(numberOfEdge[adj[i]] < K)
                q.push(adj[i]);
        }
    }

    cout << N-cnt << endl;

    return 0;
}

void printList(vector<vector<int>> graph){
    for(int i=1;i<graph.size();i++){
        cout<<"["<<i<<"]: ";
        for(int j=0;j<graph[i].size();j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}

void printArr(int N, int arr[]){
    for(int i=1;i<=N;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}