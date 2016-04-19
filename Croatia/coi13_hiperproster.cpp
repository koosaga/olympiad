#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
   
vector<pi> graph[505];
   
int n, m, s, e;
int sp[505][505];
int vis_last;
   
void solve(){
    scanf("%d %d",&s,&e);
    bool inque[250505] = {};
    queue<pi> pq;
    pq.push(pi(0, s*n));
    inque[s*n] = 1;
    sp[s][n] = 0;
    while (!pq.empty()) {
        pi t = pq.front();
        pq.pop();
        inque[t.second] = 0;
        int p1 = (t.second / n), p2 = t.second % n;
        if(sp[p1][p2] < t.first) continue;
        if(p1 == e) vis_last = 1;
        for (int i=0; i<graph[p1].size(); i++) {
            pi x = graph[p1][i];
            if(x.first == -1){
                if(p2+1 < n && sp[x.second][p2+1] > t.first){
                    sp[x.second][p2+1] = t.first;
                    if(!inque[n * x.second + p2 + 1]) pq.push(pi(t.first,n * x.second+ p2 + 1));
                }
            }
            else{
                if(p2 < n && sp[x.second][p2] > t.first + x.first){
                    sp[x.second][p2] = t.first + x.first;
                    if(!inque[n * x.second + p2]) pq.push(pi(t.first + x.first,n * x.second + p2));
                }
            }
        }
    }
}
   
struct hull{
    int la[1005], lb[1005], sz;
    void init(){ sz = 0; }
    double cross(int x, int y){
        return (lb[y] - lb[x]) * 1.0 / (la[x] - la[y]);
    }
    void insert(int p, int q){
        la[sz] = p;
        lb[sz] = q;
        if(sz && lb[sz] >= lb[sz-1]) return;
        while(sz >= 2 && cross(sz,sz-1) > cross(sz-1,sz-2)){
            la[sz-1] = la[sz];
            lb[sz-1] = lb[sz];
            sz--;
        }
        sz++;
    }
    long long f(int p, int x){
        return 1ll * la[p] * x + lb[p];
    }
}hull;
   
void print(){
    if(vis_last == 0) puts("0 0");
    else if(sp[e][0] > 1e9) puts("inf");
    else{
        hull.init();
        for (int i=0; i<n; i++) {
            if(sp[e][i] < 1e9){
                hull.insert(i,sp[e][i]);
            }
        }
        if(hull.sz == 1){
            printf("1 %d",sp[e][0]);
        }
        else{
            int r = (int)(hull.cross(0,1) + 0.99999);
            printf("%d ",r);
            int p = 1;
            long long ret = 0;
            for (int i=hull.sz-1; i; i--) {
                int end = (int)hull.cross(i,i-1);
                end = min(end,r);
                ret += (hull.f(i,end) + hull.f(i,p)) * (end - p + 1) / 2;
                p = end + 1;
            }
            ret += 1ll * sp[e][0] * (r - p + 1);
            printf("%lld",ret);
        }
        puts("");
    }
}
   
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int x,y,z;
        char str[10];
        scanf("%d %d",&x,&y);
        scanf("%s",str);
        if(str[0] == 'x') z=-1;
        else sscanf(str,"%d",&z);
        graph[x].push_back(pi(z,y));
    }
    int q;
    scanf("%d",&q);
    while (q--) {
        vis_last = 0;
        memset(sp, 0x3f, sizeof(sp));
        solve();
        print();
    }
}