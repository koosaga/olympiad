#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,int> pi;
  
struct disj{
    int pa[100005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        find(q);
        return 1;
    }
}disj1, disj2;
  
int n, m;
pi bri[100005];
vector<int> graph[100005];
  
int par[100005][17], dep[100005];
bool vis[100005];
  
void dfs(int x, int pa){
    vis[x] = 1;
    par[x][0] = pa;
    for (auto &i : graph[x]){
        if(i == pa) continue;
        dep[i] = dep[x] + 1;
        dfs(i,x);
    }
}
  
int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x,y);
    int dx = dep[x] - dep[y];
    for(int i=0; i<17; i++){
        if((dx >> i) & 1) x = par[x][i];
    }
    for(int i=16; i>=0; i--){
        if(par[x][i] != par[y][i]){
            x = par[x][i];
            y = par[y][i];
        }
    }
    if(x != y) x = par[x][0];
    return x;
}
  
int up[100005];
  
void dfs2(int x, int pa){
    vis[x] = 1;
    for (auto &i : graph[x]){
        if(i == pa) continue;
        dfs2(i,x);
        up[x] = max(up[x], up[i] - 1);
    }
    if(pa != 0 && up[x] == 0) printf("%d %d\n",pa,x);
}

int main(){
    scanf("%d %d\n",&n,&m);
    disj1.init(n);
    disj2.init(n);
    int c = 0;
    while(m--){
        int u = 0, v = 0;
        char str[15];
        fgets(str,15,stdin);
        int pos = 0;
        while(str[pos] != ' '){
            u = (10 * u) + (str[pos] - '0');
            pos++;
        }
        pos++;
        while(str[pos] != '\n' && str[pos]){
            v = (10 * v) + (str[pos] - '0');
            pos++;
        }
        if(disj1.uni(u,v)){
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        else if(disj2.uni(u,v)) bri[c++] = pi(u, v);
    }
    for(int i=1; i<=n; i++){
        if(!vis[i]) dfs(i, 0);
    }
    memset(vis, 0, sizeof(vis));
    for(int i=1; i<17; i++){
        for(int j=1; j<=n; j++){
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }
    for(int k=0; k<c; k++){
        pi i = bri[k];
        int l = lca(i.first,i.second);
        up[i.first] = max(up[i.first],dep[i.first] - dep[l]);
        up[i.second] = max(up[i.second],dep[i.second] - dep[l]);
    }
    for(int i=1; i<=n; i++){
        if(!vis[i]) dfs2(i, 0);     
    }
}