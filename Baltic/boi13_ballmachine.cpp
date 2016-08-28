#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
  
int n, q;
  
int dfn[100005], rev[100005];
int par[100005][17];
int dep[100005];
vector<int> graph[100005];
  
int piv;
int root;
 
int min_sub[100005];
 
int prep(int x){
    min_sub[x] = x;
    for(int ii=0; ii<graph[x].size(); ii++){
        int i = graph[x][ii];
        min_sub[x] = min(min_sub[x],prep(i));
    }
    return min_sub[x];
}
 
bool cmp(int a, int b){
    return min_sub[a] < min_sub[b];
}
 
void dfs(int x){
    for(int i=1; i<17; i++){
        par[x][i] = par[par[x][i-1]][i-1];
    }
    for(int ii=0; ii<graph[x].size(); ii++){
        int i = graph[x][ii];
        dep[i] = dep[x] + 1;
        dfs(i);
    }
    dfn[x] = ++piv;
    rev[dfn[x]] = x;
}
 
set<int> s;
 
int main(){
    scanf("%d %d",&n,&q);
    for(int i=1; i<=n; i++){
        s.insert(i);
        scanf("%d",&par[i][0]);
        if(par[i][0]) graph[par[i][0]].push_back(i);
        else root = i;
    }
    prep(root);
    for(int i=1; i<=n; i++){
        sort(graph[i].begin(), graph[i].end(),cmp);
    }
    dfs(root);
    while(q--){
        int a, b;
        scanf("%d %d",&a,&b);
        if(a == 1){
            int p;
            while(b--) p = *s.begin(), s.erase(s.begin());
            printf("%d\n",rev[p]);
        }
        else{
            int op = dep[b];
            for(int i=16; i>=0; i--){
                if(par[b][i] == 0) continue;
                if(s.find(dfn[par[b][i]]) == s.end()){
                    b = par[b][i];
                }
            }
            s.insert(dfn[b]);
            printf("%d\n",op - dep[b]);
        }
    }
}