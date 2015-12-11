#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
pi a[50005], b[50005], t;
int n;
 
vector<pi> ha, hb;
 
int ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    long long t = 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
    if(t > 0) return 1;
    if(t == 0) return 0;
    return -1;
}
 
long long hypot(int x, int y){
    return 1ll * x * x + 1ll * y * y;
}
 
bool cmp(pi a, pi b){
    int tmp = ccw(t, a, b);
    if(tmp != 0) return tmp > 0;
    return hypot(a.first - t.first, a.second - t.second) <= hypot(b.first - t.first, b.second - t.second);
}
 
void make_hull(pi *a, vector<pi> &hull){
    swap(a[0],*min_element(a,a+n));
    t = a[0];
    sort(a+1,a+n,cmp);
    for(int i=0; i<n; i++){
        while(hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), a[i]) != 1){
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }
}
 
bool insideln(pi a, pi b, pi c){
    int minx = min(a.first, c.first), maxx = max(a.first, c.first);
    int miny = min(a.second, c.second), maxy = max(a.second,c.second);
    if(ccw(a,c,b) == 0 && minx <= b.first && b.first <= maxx && miny <= b.second && b.second <= maxy){
        return 1;
    }
    return 0;
}
 
int process(pi *a, vector<pi> &hull){
    vector<pi> obj;
    t = hull[0];
    for(int i=0; i<n; i++){
        if(a[i].first < hull[0].first) continue;
        obj.push_back(a[i]);
    }
    sort(obj.begin(), obj.end(), cmp);
    int pt = 0, ret = 0;
    for(int i=1; i<(int)hull.size() - 1; i++){
        while(pt < obj.size() && ccw(hull[0], obj[pt], hull[i]) == 1) pt++;
        int e = pt;
        while(e < obj.size() && ccw(hull[0], obj[e], hull[i+1]) != -1) e++;
        for(int j=pt; j<e; j++){
            if(ccw(hull[i], hull[i+1], obj[j]) != -1) ret++;
        }
        pt = e;
    }
    return ret;
}
 
int main(){
    //freopen("curling.in","r",stdin);
//  freopen("curling.out","w",stdout);
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first,&a[i].second);
    }   
    for(int i=0; i<n; i++){
        scanf("%d %d",&b[i].first,&b[i].second);
    }
    make_hull(a, ha);
    make_hull(b, hb);
    int ret1 = 0, ret2 = 0;
    for(int i=0; i<n; i++){
        if(ha.size() == 2){
            if(insideln(ha[0], b[i], ha[1])) ret1++;
        }
        if(hb.size() == 2){
            if(insideln(hb[0], a[i], hb[1])) ret2++;
        }
    }
    if(ha.size() != 2){
        ret1 += process(b, ha);
    }
    if(hb.size() != 2){
        ret2 += process(a, hb);
    }
    printf("%d %d",ret1,ret2);
}