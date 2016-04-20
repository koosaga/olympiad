#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
struct edge{int s,e,x;}a[200005];
bool cmp(edge a, edge b){return a.x > b.x;}
 
struct uft{
    int pa[100005],r[100005];
    void init(int n){
        memset(r,0,sizeof(r));
        for(int i=0; i<=n; i++){
            pa[i] = i;
        }
    }
    int find(int x){
        if(pa[x] == x) return x;
        else return pa[x] = find(pa[x]);
    }
    void uni(int p, int q){
        p = find(p);
        q = find(q);
        if(r[p] < r[q]) pa[q] = p;
        else pa[p] = q;
        if(r[p] == r[q]) r[p]++;
    }
}kru;
 
int dist[100005],m,k,n,q;
vector<pi> tree[100005];
 
void extract_tree(){
    priority_queue<pi,vector<pi>,greater<pi> > pq;
    vector<pi> graph[100005];
    scanf("%d %d %d %d",&n,&m,&k,&q);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
        graph[a[i].s].push_back(pi(a[i].x,a[i].e));
        graph[a[i].e].push_back(pi(a[i].x,a[i].s));
    }
    for (int i=0; i<k; i++) {
        int t;
        scanf("%d",&t);
        pq.push(pi(0,t));
    }
    int v[100005] = {};
    while (!pq.empty()) {
        pi x = pq.top();
        pq.pop();
        if(v[x.second]) continue;
        v[x.second] = 1;
        dist[x.second] = x.first;
        for (int i=0; i<graph[x.second].size(); i++) {
            pi y = graph[x.second][i];
            if(!v[y.second]) pq.push(pi(y.first + x.first,y.second));
        }
    }
    for (int i=0; i<m; i++) {
        a[i].x = min(dist[a[i].s],dist[a[i].e]);
    }
    sort(a,a+m,cmp);
    kru.init(n);
    for (int i=0; i<m; i++) {
        if(kru.find(a[i].s) != kru.find(a[i].e)){
            kru.uni(a[i].s,a[i].e);
            tree[a[i].s].push_back(pi(a[i].x,a[i].e));
            tree[a[i].e].push_back(pi(a[i].x,a[i].s));
        }
    }
}
 
int depth[100005];
int pa[100005][17], minv[100005][17];
 
void dfs(int x, int p, int e, int d){
    if(x != 1){
        pa[x][0] = p;
        minv[x][0] = e;
        depth[x] = d;
        int tmp = p;
        for (int i=1; (1<<i) <= d; i++) {
            pa[x][i] = pa[tmp][i-1];
            minv[x][i] = min(minv[x][i-1],minv[tmp][i-1]);
            tmp = pa[x][i];
        }
    }
    for (int i=0; i<tree[x].size(); i++) {
        if(tree[x][i].second == p) continue;
        dfs(tree[x][i].second,x,tree[x][i].first,d+1);
    }
}
 
int query(int a, int b){
    int r = 1e9;
    int diff = depth[b] - depth[a];
    for (int i=0; diff; i++) {
        if(diff&1){
            r = min(r,minv[b][i]);
            b = pa[b][i];
        }
        diff >>= 1;
    }
    for (int i=16; i>=0; i--) {
        if(pa[a][i] != pa[b][i]){
            r = min(r,min(minv[a][i],minv[b][i]));
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    if(a != b){
        r = min(r,min(minv[a][0],minv[b][0]));
    }
    return r;
}
 
int main(){
    extract_tree();
    dfs(1,0,0,0);
    for (int i=0; i<q; i++) {
        int t,u;
        scanf("%d %d",&t,&u);
        if(depth[t] > depth[u]) swap(t,u);
        printf("%d\n",query(t,u));
    }
}