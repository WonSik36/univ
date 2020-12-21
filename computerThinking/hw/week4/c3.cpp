#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

void bfs(int root, long long * distArr);

vector<vector<int>> g(40001);
long long distFromN[40001];
long long distFromOne[40001];
long long distFromTwo[40001];
int p, q, r, N, M;

int main(){
    cin >> p >> q >> r >> N >> M;

    for(int i=0;i<M;i++){
        int start, end;

        cin >> start >> end;

        g[start].push_back(end);
        g[end].push_back(start);
    }

    for(int i=1;i<=40000;i++){
        distFromN[i] = -1;
        distFromOne[i] = -1;
        distFromTwo[i] = -1;
    }

    bfs(1, distFromOne);
    bfs(2, distFromTwo);
    bfs(N, distFromN);

    long long min = 9223372036854775807L;
    for(int i=1;i<=N;i++){
        if(distFromN[i] == -1)
            continue;
        long long dist = distFromN[i] * r + distFromOne[i] * p + distFromTwo[i] * q;
        min = min < dist ? min : dist;
    }

    cout << min << endl;

    return 0;
}

void bfs(int root, long long * distArr){
    bool visited[40001] = {false,};

    queue<pair<int,int>> q;
    q.push(make_pair(root, 0));
    while(!q.empty()){
        pair<int,int> head = q.front();
        q.pop();

        if(visited[head.first])
            continue;
        visited[head.first] = true;

        distArr[head.first] = head.second;

        for(vector<int>::iterator adj = g[head.first].begin(); adj!=g[head.first].end(); adj++){
            if(visited[*adj])
                continue;

            q.push(make_pair(*adj, head.second+1));
        }
    }   
}