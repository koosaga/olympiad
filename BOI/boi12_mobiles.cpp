#include <cstdio>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
 
int n, l, x[1000005], y[1000005];
 
struct segs{
    double st, ed, x, y;
    segs(double s, double e, pi t){
        st = s, ed = e, x = t.first, y = t.second;
    }
};
 
vector<pi> points;
deque<pi> dq;
vector<segs> v;
 
double cross(pi a, pi b){
    int x1 = a.first, x2 = b.first, y1 = a.second, y2 = b.second;
    return 1.0 * (1ll * x2 * x2 + 1ll * y2 * y2 - 1ll * x1 * x1 - 1ll * y1 * y1) / (2.0 * (x2 - x1));
}
 
double dist(pi a, pi b){
    return hypot(a.first - b.first,a.second - b.second);
}
 
int main(){
    scanf("%d %d",&n,&l);
    for (int i=0; i<n; i++) {
        int x, y;
        scanf("%d %d",&x,&y);
        if(y < 0 ) y = -y;
        points.push_back(pi(x,y));
    }
    sort(points.begin(),points.end());
    for (int i=0; i<points.size();) {
        int e = i;
        while (e < points.size() && points[e].first == points[i].first) {
            e++;
        }
        int x = points[i].first, y = points[i].second;
        while (dq.size() >= 2 && cross(dq[dq.size()-2],dq.back()) > cross(dq.back(),pi(x,y))) {
            dq.pop_back();
        }
        dq.push_back(pi(x,y));
        i = e;
    }
    while (dq.size() >= 2 && cross(dq[0],dq[1]) < 0) dq.pop_front();
    while (dq.size() >= 2 && cross(dq[dq.size()-2],dq.back()) > l) dq.pop_back();
    v.push_back(*new segs(0,cross(dq[0],dq[1]),dq.front()));
    for (int i=0; i<dq.size()-2; i++) {
        v.push_back(*new segs(cross(dq[i],dq[i+1]),cross(dq[i+1],dq[i+2]),dq[i+1]));
    }
    v.push_back(*new segs(cross(dq[dq.size()-2],dq.back()),l,dq.back()));
    double ret = 0;
    for(int i=0; i<v.size(); i++){
        ret = max(ret,max(hypot(v[i].st - v[i].x, v[i].y), hypot(v[i].ed - v[i].x,v[i].y)));
    }
    printf("%lf",ret);
}