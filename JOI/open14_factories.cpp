#include "factories.h"
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<lint,int> pi;
 
vector<pi> graph[500005];
 
int piv, dfn[500005];
int dep[500005], sz[500005];
lint dist[500005];
int pa[500005][19];
 
int dfs(int x, int par, int d, lint t){
    dep[x] = d;
    dfn[x] = ++piv;
    dist[x] = t;
    pa[x][0] = par;
    sz[x] = 1;
    for (int i=1; (1<<i) <= dep[x]; i++) {
        pa[x][i] = pa[pa[x][i-1]][i-1];
    }
    for (pi &i : graph[x]){
        if(par == i.second) continue;
        sz[x] += dfs(i.second,x,d+1,t + i.first);
    }
    return sz[x];
}
 
void Init(int N, int A[], int B[], int D[]){
    for (int i=0; i<N-1; i++) {
        graph[A[i]+1].push_back(pi(D[i],B[i]+1));
        graph[B[i]+1].push_back(pi(D[i],A[i]+1));
    }
    dfs(1,0,0,0);
}
 
int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x,y);
    int dx = dep[x] - dep[y];
    for (int i=0; (1<<i) <= dx; i++) {
        if(dx & (1<<i)) {
            x = pa[x][i];
        }
    }
    for (int i=18; i>=0; i--) {
        if(pa[x][i] != pa[y][i]){
            x = pa[x][i];
            y = pa[y][i];
        }
    }
    if(x != y) x = pa[x][0];
    return x;
}
 
bool cmp(int a, int b){
    return dfn[a] < dfn[b];
}
 
vector<pi> g2[500005];
vector<int> pos;
int c;
int vis_stamp[500005];
int object[500005];
 
int pivot;
 
void const_g(){
    int cp = pos[pivot];
    int sentinel = dfn[cp] + sz[cp] - 1;
    pivot++;
    while(pivot < pos.size() && dfn[pos[pivot]] <= sentinel){
        g2[cp].push_back(pi(dist[pos[pivot]] - dist[cp],pos[pivot]));
        g2[pos[pivot]].push_back(pi(dist[pos[pivot]] - dist[cp],cp));
        const_g();
    }
}
 
lint dijkstra(int n, int* s){
    priority_queue<pi,vector<pi>,greater<pi> > pq;
    for (int i=0; i<n; i++) {
        pq.push(pi(0ll,s[i] + 1));
    }
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        if(vis_stamp[t.second] == c) continue;
        vis_stamp[t.second] = c;
        if(object[t.second] == c){
            return t.first;
        }
        for (pi &i : g2[t.second]){
            if(vis_stamp[i.second] == c) continue;
            pq.push(pi(t.first + i.first, i.second));
        }
    }
    return -1;
}
 
lint Query(int S, int X[], int T, int Y[]){
    pivot = 0;
    c++;
    for (int i=0; i<S; i++) {
        pos.push_back(X[i]+1);
    }
    for (int i=0; i<T; i++) {
        object[Y[i]+1] = c;
        pos.push_back(Y[i]+1);
    }
    sort(pos.begin(),pos.end(),cmp);
    int p = (int)pos.size() - 1;
    for (int i=0; i<p; i++) {
        pos.push_back(lca(pos[i],pos[i+1]));
    }
    sort(pos.begin(),pos.end(),cmp);
    pos.resize(unique(pos.begin(),pos.end()) - pos.begin());
    const_g();
    lint ret = dijkstra(S,X);
    for (int &i : pos){
        g2[i].clear();
    }
    pos.clear();
    return ret;
}