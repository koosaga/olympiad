#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int n;
int adj[1005][1005];
int dist[1005], vis[1005], par[1005];
 
int dijk(){
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[1] = 0;
    while(1){
        int minv = 1e9, minp = -1;
        for(int i=1; i<=n; i++)if(!vis[i] && minv > dist[i]){
            minv = dist[i];
            minp = i;
        }
        vis[minp] = 1;
        if(minp == n) return dist[n];
        for(int i=1; i<=n; i++){
            if(adj[minp][i] && !vis[i] && dist[i] > dist[minp] + adj[minp][i]){
                dist[i] = dist[minp] + adj[minp][i];
                par[i] = minp;
            }
        }
    }
    return -1;
}
 
int main(){
    int m;
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        adj[s][e] = adj[e][s] = x;
    }
    dijk();
    int pos = n, ret = 0;
    int parr[1005];
    memcpy(parr,par,sizeof(par));
    while(pos != 1){
        int pa = parr[pos];
        int p = adj[pa][pos];
        adj[pa][pos] = adj[pos][pa] = 1e9;
        ret = max(ret,dijk());
        adj[pa][pos] = adj[pos][pa] = p;
        pos = pa;
    }
    printf("%d",ret);
}