#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
 
int n,m;
inline int NOT(int x){return x > m ? x-m : x+m;}
 
vector<int> graph[1000005], rev[1000005], ts;
 
int vis[1000005];
int comp[1000005], piv;
 
void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    for (int i=0; i<graph[x].size(); i++) {
        dfs(graph[x][i]);
    }
    ts.push_back(x);
}
 
void dfs2(int x, int y){
    if(vis[x]) return;
    vis[x] = 1;
    comp[x] = y;
    for (int i=0; i<rev[x].size(); i++) {
        dfs2(rev[x][i],y);
    }
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        int a,b,c,d;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        if(b == 0) a = NOT(a);
        if(d == 0) c = NOT(c);
        graph[NOT(a)].push_back(c);
        rev[c].push_back(NOT(a));
        graph[NOT(c)].push_back(a);
        rev[a].push_back(NOT(c));
    }
    for (int i=1; i<=2*m; i++) {
        if(!vis[i]){
            dfs(i);
        }
    }
    memset(vis,0,sizeof(vis));
    for (int i=(int)ts.size()-1; i>=0; i--){
        if(!vis[ts[i]]){
            dfs2(ts[i],++piv);
        }
    }
    for (int i=1; i<=m; i++) {
        if(comp[i] == comp[i+m]){
            puts("IMPOSSIBLE");
            return 0;
        }
    }
    for (int i=1; i<=m; i++) {
        printf("%d\n",comp[i] > comp[i+m]);
    }
}