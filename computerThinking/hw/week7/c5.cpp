#include <stdio.h>
#include <vector>
#include <utility>

using namespace std;

int N;
vector<pair<int,double>> balloons;
int main(){
    scanf("%d", &N);

    for(int i=0;i<N;i++){
        int x, r;
        scanf("%d %d", &x, &r);

        double min_radius = (double)r;
        double max_radius;
        for(int j=balloons.size()-1; j >= 0; j--){
            if(j == balloons.size()-1){
                double calc_radius = ((double)(balloons[j].first - x) * (balloons[j].first - x)) / (4 * balloons[j].second);
                min_radius = min_radius < calc_radius ? min_radius : calc_radius;
                max_radius = balloons[j].second;
                continue;
            }

            if(max_radius >= min_radius)
                break;

            if(balloons[j].second > max_radius){
                double calc_radius = ((double)(balloons[j].first - x) * (balloons[j].first - x)) / (4 * balloons[j].second);
                min_radius = min_radius < calc_radius ? min_radius : calc_radius;
                max_radius = balloons[j].second;
            }
        }

        balloons.push_back(make_pair(x, min_radius));
    }

    for(int i=0; i<N; i++){
        printf("%.3f\n", balloons[i].second);
    }

    return 0;
}