#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
vector<pi> graph[100005];
vector<pi> odd_cyc, backedg;
 
int n, m;
int par[100005][17], dep[100005], low[100005], dfn[100005], piv;
 
bool vis[100005];
bool vise[200005];
 
int cutedge;
int gap[100005];
 
void dfs(int x){
    low[x] = dfn[x] = ++piv;
    for(int i=1; i<=16; i++){
        par[x][i] = par[par[x][i-1]][i-1];
    }
    for(auto &i : graph[x]){
        if(!vis[i.second]){
            vise[i.first] = 1;
            vis[i.second] = 1;
            dep[i.second] = dep[x] + 1;
            par[i.second][0] = x;
            dfs(i.second);
            low[x] = min(low[x], low[i.second]);
        }
        else{
            if(vise[i.first]) continue;
            vise[i.first] = 1;
            low[x] = min(low[x], dfn[i.second]);
            if((dep[x] - dep[i.second]) % 2 == 0){
                odd_cyc.push_back(pi(i.second, x));
            }
            else backedg.push_back(pi(i.second, x));
        }
    }
    if(par[x][0] && low[x] == dfn[x]){
        cutedge++;
    }
}
 
int lca(int s, int e){
    if(dep[s] > dep[e]) swap(s,e);
    int dx = dep[e] - dep[s];
    for(int i=0; i<17; i++){
        if((dx >> i) & 1) e = par[e][i];
    }
    for(int i=16; i>=0; i--){
        if(par[s][i] != par[e][i]){
            s = par[s][i];
            e = par[e][i];
        }
    }
    if(s != e) return par[s][0];
    return s;
}
 
bool vis2[100005];
int dx[100005];
int cnts;
 
void fill(int x){
    for(auto &i : graph[x]){
        if(!vis2[i.second]){
            vis2[i.second] = 1;
            fill(i.second);
            dx[x] += dx[i.second];
        }
    }
    if(par[x][0] && dx[x] == odd_cyc.size()){
        cnts++;
    }
}
 
int solve(int x){
    cnts = 0;
    for(auto &i : odd_cyc){
        dx[i.first]++;
        dx[i.second]++;
        dx[lca(i.first, i.second)]-=2;
    }
    for(auto &i : backedg){
        dx[i.first]--;
        dx[i.second]--;
        dx[lca(i.first, i.second)]+=2;
    }
    vis2[x] = 1;
    fill(x);
    return cnts;
}
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        graph[s].push_back(pi(i, e));
        graph[e].push_back(pi(i, s));
    }
    int bad = 0, cnt = 0;
    for(int i=1; i<=n; i++){
        if(!vis[i]){
            vis[i] = 1;
            odd_cyc.clear();
            backedg.clear();
            cutedge = 0;
            dfs(i);
            if(odd_cyc.empty()){
                if(!bad) cnt += cutedge;
            }
            else{
                if(bad){
                    puts("0");
                    return 0;
                }
                bad = 1;
                cnt = solve(i) + (odd_cyc.size() == 1);
            }
        }
    }
    printf("%d",cnt);
}