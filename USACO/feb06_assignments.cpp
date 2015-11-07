#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct edg{int pos, cap, rev;};

vector<edg> graph[1025];

int n,m;
int a[1001][21];
int cost[21];

void add_edge(int s, int e, int x){
    graph[s].push_back({e,x,(int)graph[e].size()});
    graph[e].push_back({s,0,(int)graph[s].size()-1});
}

void graph_init(int s, int e){
    for (int i=0; i<=n+m+1; i++) {
        graph[i].clear();
    }
    for (int i=1; i<=n; i++) {
        add_edge(0,i,1);
    }
    for (int i=1; i<=m; i++) {
        add_edge(n+i,n+m+1,cost[i]);
    }
    for (int i=s; i<=e; i++) {
        for (int j=1; j<=n; j++){
            add_edge(j,a[j][i]+n,1);
        }
    }
}

int vis[1050], pa[1050], pe[1050];

int dfs(int x){
    if(x == n+m+1) return 1;
    vis[x] = 1;
    for (int i=0; i<graph[x].size(); i++) {
        edg e = graph[x][i];
        if(!vis[e.pos] && e.cap > 0 && dfs(e.pos)){
            pa[e.pos] = x;
            pe[e.pos] = i;
            return 1;
        }
    }
    return 0;
}

int flow(){
    int ret = 0;
    while (1) {
        memset(vis,0,sizeof(vis));
        memset(pa,0,sizeof(pa));
        memset(pe,0,sizeof(pe));
        if(!dfs(0)) break;
        ret++;
        int pos = n+m+1;
        while (pos) {
            edg e = graph[pa[pos]][pe[pos]];
            graph[pa[pos]][pe[pos]].cap--;
            graph[pos][e.rev].cap++;
            pos = pa[pos];
        }
    }
    return ret;
}

int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    for (int j=1; j<=m; j++) {
        scanf("%d",&cost[j]);
    }
    for (int i=1; i<=m; i++) {
        for (int j=1; j+i-1<=m; j++) {
            graph_init(j,j+i-1);
            if(flow() == n){
                printf("%d",i);
                return 0;
            }
        }
    }
}