#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int n,m;
int s[205], e[205];
long long adj[205][205];

struct edg{int pos,cap,rev;};

vector<edg> graph[405];
int dist[405];

void add_edge(int s, int e, int cap){
    graph[s].push_back({e,cap,(int)graph[e].size()});
    graph[e].push_back({s,0,(int)graph[s].size()-1});
}

bool get_level(){
    memset(dist,0,sizeof(dist));
    queue<int> q;
    q.push(0);
    int vis[405] = {};
    vis[0] = 1;
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        for (int i=0; i<graph[qf].size(); i++) {
            if(!vis[graph[qf][i].pos] && graph[qf][i].cap > 0){
                q.push(graph[qf][i].pos);
                vis[graph[qf][i].pos] = 1;
                dist[graph[qf][i].pos] = dist[qf] + 1;
            }
        }
    }
    if(!vis[2*n+1]) return 0;
    return 1;
}

int vis[505];

int get_augpath(int x, int cap){
    if(x == 2*n+1) return cap;
    for (int i=0; i<graph[x].size(); i++) {
        edg e = graph[x][i];
        if(!vis[e.pos] && dist[e.pos] == dist[x] + 1 && e.cap > 0){
            int p = get_augpath(e.pos,min(cap,e.cap));
            if(p > 0){
                graph[x][i].cap -= p;
                graph[e.pos][e.rev].cap += p;
                return p;
            }
        }
    }
    vis[x] = 1;
    return 0;
}

bool trial(long long t){
    for (int i=0; i<2*n+2; i++) {
        graph[i].clear();
    }
    int sm = 0;
    for (int i=1; i<=n; i++) {
        sm += s[i];
        add_edge(0,i,s[i]);
        add_edge(i+n,2*n+1,e[i]);
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if(adj[i][j] <= t){
                add_edge(i,j+n,1000);
            }
        }
    }
    while (get_level()) {
        memset(vis,0,sizeof(vis));
        while(1){
            int t = get_augpath(0,1e9);
            if(t == 0) break;
            sm -= t;
        }
    }
    return sm == 0;
}

int main(){
    memset(adj,0x3f,sizeof(adj));
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&s[i],&e[i]);
    }
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        adj[e][s] = adj[s][e] = min(adj[s][e],1ll * x);
    }
    for (int i=1; i<=n; i++) {
        adj[i][i] = 0;
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            for (int k=1; k<=n; k++) {
                adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
            }
        }
    }
    long long s = 0, e = 3e11;
    while (s != e) {
        long long m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    if(e > 2e11) puts("-1");
    else printf("%lld",e);
}