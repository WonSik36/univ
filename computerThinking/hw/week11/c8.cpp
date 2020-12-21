#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <math.h>

using namespace std;

double calc_dist(pair<int, int>* p1, pair<double, double>* p2);
double calc_well_max_right_point(pair<int,int>* p);

class Compare{
public:
    bool operator() (pair<int, int> l, pair<int, int> r){
        if(l.first > r.first) {
            return true;
        } else if(l.first < r.first) {
            return false;
        } else {
            if(l.second < r.second) 
                return true;
            else
                return false;
        }
    }
};

int N, D;
int main() {
    cin >> N >> D;

    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    for(int i=0;i<N;i++){
        int x, y;
        cin >> x >> y;
        pq.push(make_pair(x, y));
    }

    vector<pair<int, int>> vilages;
    while(!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();

        vilages.push_back(p);
    }

    vector<pair<double, double>> wells;
    wells.push_back(make_pair(calc_well_max_right_point(&vilages[0]), 0));
    for(int i=1;i<N;i++){
        if(calc_dist(&vilages[i], &(wells.back())) <= D)
            continue;

        if(vilages[i].first < wells.back().first) {
            wells.back().first = calc_well_max_right_point(&vilages[i]);
        } else {
            wells.push_back(make_pair(calc_well_max_right_point(&vilages[i]), 0));
        }
    }

    cout << wells.size() << endl;

    return 0;
}

double calc_dist(pair<int, int>* p1, pair<double, double>* p2) {
    int x1 = p1->first;
    int y1 = p1->second;
    double x2 = p2->first;
    double y2 = p2->second;

    return sqrt((double)((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

double calc_well_max_right_point(pair<int,int>* p) {
    int x = p->first;
    int y = p->second;
    return x + sqrt(D*D - y*y);
}