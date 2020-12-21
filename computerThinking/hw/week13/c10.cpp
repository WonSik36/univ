#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;


class Compare {
public:
    bool operator() (pair<int, int> l, pair<int, int> r){
        if(l.first > r.first)
            return true;
        else if(l.first < r.first)
            return false;
        else {
            if(l.second > r.second) {
                return true;
            } else {
                return false;
            }
        }
    }
};

int binary_search(vector<pair<int, int>>* v, pair<int, int>* p);
int bfs(int start, bool* visited);

int dx[] = {0,1,2,3,4,5};
int dy1[] = {1,-4,-4,-4,-3,0};
int dy2[] = {5,4,4,4,3,0};
vector<int> g[50001];

int main() {
    int N;
    cin >> N;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    for(int i=0;i<N;i++){
        int x, y;
        cin >> x >> y;

        pq.push(make_pair(x,y));
    }

    vector<pair<int, int>> buildings;
    for(int i=0;i<N;i++){
        pair<int, int> p = pq.top();
        pq.pop();

        buildings.push_back(p);
    }

    
    for(int i=0;i<N;i++) {
        pair<int, int> p = buildings[i];

        for(int j=0;j<6;j++) {
            int bx = p.first+dx[j];
            int by1 = p.second+dy1[j];
            int by2 = p.second+dy2[j];

            pair<int, int> upper_bound = make_pair(bx, by2);
            int idx = binary_search(&buildings, &upper_bound);

            for(int k=idx; buildings[k].first == bx && buildings[k].second >= by1 && buildings[k].second <= by2; k--) {
                g[i].push_back(k);
                g[k].push_back(i);
            }
        }
    }

    int sum = 0;
    bool* visited = new bool[N];
    for(int i=0;i<N;i++){
        visited[i] = false;
    }

    for(int i=0;i<N;i++){
        if(visited[i])
            continue;

        sum += bfs(i, visited);
    }

    cout << sum << endl;
    
    delete[] visited;

    return 0;
}

int binary_search(vector<pair<int, int>>* v, pair<int, int>* p) {
    int l = 0, r = v->size();

    while(l+1 < r) {
        int mid = (l+r) / 2;

        if((*v)[mid].first < p->first) {
            l = mid;
        } else if((*v)[mid].first > p->first) {
            r = mid;
        } else {
            if((*v)[mid].second < p->second) {
            l = mid;
            } else if((*v)[mid].second > p->second) {
                r = mid;
            } else {
                return mid;
            }
        }
    }

    return l;
}

int bfs(int start, bool* visited) {
    int red = 0, black = 0;

    visited[start] = true;
    int start_color = 0;
    
    queue<pair<int,int>> q;
    q.push(make_pair(start, start_color));

    while(!q.empty()) {
        pair<int,int> node = q.front();
        q.pop();

        if(node.second == 0)
            red++;
        else
            black++;

        for(int i=0;i<g[node.first].size();i++){
            int next = g[node.first][i];
            
            if(visited[next])
                continue;
            visited[next] = true;

            int next_color = node.second == 0 ? 1 : 0;
            q.push(make_pair(next, next_color));
        }
    }

    return red < black ? red : black;
}