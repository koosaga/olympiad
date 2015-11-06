#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;
 
struct line{
    int sx, sy, ex, ey;
};
 
lint hypot(int x, int y){
    return 1ll * x * x + 1ll * y * y;
}
 
bool cmp(line a, line b){
    int ax = a.sx + a.ex;
    int bx = b.sx + b.ex;
    int ay = a.sy + a.ey;
    int by = b.sy + b.ey;
    if(ax != bx) return ax < bx;
    if(ay != by) return ay < by;
    return hypot(a.ex - a.sx,a.ey - a.sy) < hypot(b.ex - b.sx,b.ey - b.sy);
}
 
lint cross(pi a, pi b){
    lint t = 1ll * a.first * b.second - 1ll * b.first * a.second;
    return t / 2;
}
 
lint product(pi a, pi b){
    return 1ll * a.first * b.first + 1ll * a.second * b.second;
}
 
bool cmp2(pi a, pi b){
    return cross(a,b) > 0;
}
 
int n, x[1505], y[1505];
vector<line> v;
vector<pi> low, high;
 
lint solve(int s, int e){
    low.clear();
    high.clear();
    for (int i=s; i<=e; i++) {
        pi t1(v[i].ex - v[i].sx,v[i].ey - v[i].sy);
        pi t2(-t1.first,-t1.second);
        if(t1.first >= 0) high.push_back(t1);
        else low.push_back(t1);
        if(t2.first >= 0) high.push_back(t2);
        else low.push_back(t2);
    }
    sort(low.begin(),low.end(),cmp2);
    sort(high.begin(),high.end(),cmp2);
    lint ret = 0;
    int ed = 0;
    for (int i=0; i<low.size(); i++) {
        while (ed < low.size() && product(low[i],low[ed]) >= 0) {
            ed++;
        }
        ret = max(ret,cross(low[i],low[ed-1]));
        if(ed != low.size()) ret = max(ret,cross(low[i],low[ed]));
    }
    ed = 0;
    for (int i=0; i<high.size(); i++) {
        while (ed < high.size() && product(high[i],high[ed]) >= 0) {
            ed++;
        }
        ret = max(ret,cross(high[i],high[ed-1]));
        if(ed != high.size()) ret = max(ret,cross(high[i],high[ed]));
    }
    return ret;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
    }
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            v.push_back((line){x[i],y[i],x[j],y[j]});
        }
    }
    sort(v.begin(),v.end(),cmp);
    lint ret = 0;
    for (int i=0; i<v.size();) {
        int e = i;
        while (e < v.size() && cmp(v[i],v[e]) == 0){
            e++;
        }
        ret = max(ret,solve(i,e-1));
        i = e;
    }
    printf("%lld",ret);
}