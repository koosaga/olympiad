#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
 
struct edg{int pos,cap,rev;};
vector<edg> graph[405];
 
void add_edge(int s, int e, int x){
    graph[s].push_back((edg){e,x,(int)graph[e].size()});
    graph[e].push_back((edg){s,0,(int)graph[s].size()-1});
}
 
int n,m,s,e;
int pa[405], pe[405];
 
int bfs(){
    int vis[405] = {};
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int qf = q.front();
        if(qf == e) break;
        q.pop();
        for (int i=0; i<graph[qf].size(); i++) {
            edg e = graph[qf][i];
            if(vis[e.pos] || e.cap <= 0) continue;
            vis[e.pos] = 1;
            pa[e.pos] = qf;
            pe[e.pos] = i;
            q.push(e.pos);
        }
    }
    return vis[e];
}
 
int main(){
    scanf("%d %d %d %d",&n,&m,&s,&e);
    for (int i=1; i<=n; i++) {
        int t;
        scanf("%d",&t);
        add_edge(i,i+n,t);
    }
    for (int i=0; i<m; i++) {
        int p,q;
        scanf("%d %d",&p,&q);
        add_edge(p+n,q,2e9);
        add_edge(q+n,p,2e9);
    }
    e += n;
    while (bfs()) {
        int pos = e, cap = 2e9;
        while (pos != s) {
            cap = min(graph[pa[pos]][pe[pos]].cap, cap);
            pos = pa[pos];
        }
        pos = e;
        while (pos != s) {
            int rev = graph[pa[pos]][pe[pos]].rev;
            graph[pa[pos]][pe[pos]].cap -= cap;
            graph[pos][rev].cap += cap;
            pos = pa[pos];
        }
    }
    // track ans
    vector<int> ret;
    queue<int> q;
    q.push(s);
    int vis[405] = {};
    vis[s] = 1;
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        for (int i=0; i<graph[qf].size(); i++){
            edg x = graph[qf][i];
            if(!vis[x.pos] && x.cap > 0) {
                q.push(x.pos);
                vis[x.pos] = 1;
            }
        }
    }
    for (int i=1; i<=n; i++) {
        if(!vis[i]) continue;
        for (int j=0; j<graph[i].size(); j++) {
            edg x = graph[i][j];
            if(!vis[x.pos] && x.cap == 0 && x.pos == i + n) printf("%d ",i);
        }
    }
}