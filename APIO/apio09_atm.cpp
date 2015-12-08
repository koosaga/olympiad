#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
 
int n,m,s,p;
int v[500005];
vector<int> graph[500005],rev[500005];
int cst[500005];
 
vector<int> dfn;
 
int comp[500005];
vector<int> cond[500005];
int newcost[500005], canend[500005];
void dfs(int x){
    v[x] = 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(!v[graph[x][i]]) dfs(graph[x][i]);
    }
    dfn.push_back(x);
}
 
void rdfs(int x, int t){
    comp[x] = t;
    v[x] = 1;
    for (int i=0; i<rev[x].size(); i++) {
        if(!v[rev[x][i]]) rdfs(rev[x][i],t);
    }
}
 
int mem[500005];
int dp(int x){
    if(x == comp[s]) return newcost[x];
    if(mem[x]) return mem[x];
    int res = -1e9;
    for (int i=0; i<cond[x].size(); i++) {
        res = max(res,dp(cond[x][i]));
    }
    return mem[x] = res + newcost[x];
}
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        rev[y].push_back(x);
    }
    for (int i=1; i<=n; i++) {
        scanf("%d",&cst[i]);
    }
    scanf("%d %d",&s,&p);
    for (int i=1; i<=n; i++) {
        if(!v[i]) dfs(i);
    }
    memset(v,0,sizeof(v));
    int t = 0;
    for (int i=n-1; i>=0; i--) {
        if(!v[dfn[i]]) rdfs(dfn[i],++t);
    }
    for (int i=1; i<=n; i++) {
        for (int j=0; j<rev[i].size(); j++) {
            if(comp[i] != comp[rev[i][j]]) cond[comp[i]].push_back(comp[rev[i][j]]);
        }
        newcost[comp[i]] += cst[i];
    }
    for (int i=0; i<p; i++) {
        int x;
        scanf("%d",&x);
        canend[comp[x]] = 1;
    }
    int res = 0;
    for (int i=1; i<=t; i++) {
        if(canend[i]){
            res = max(res,dp(i));
        }
    }
    printf("%d",max(0,res));
}