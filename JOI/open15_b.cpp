#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> pi;

struct path{
    int cost, s, e;
};

int n, m;
vector<int> graph[100005];
vector<path> paths[100005];
int par[100005][17], dep[100005];

int dfn[100005], sz[100005], p0, tra[100005];
int comp[100005], cnum[100005], chead[100005], csize[100005], piv;
int son[100005];

int lca(int x, int y){
    if(dep[x] > dep[y]) swap(x,y);
    int diff = dep[y] - dep[x];
    for (int i=0; i<17; i++) {
        if((diff >> i) & 1) y = par[y][i];
    }
    for (int i=16; i>=0; i--) {
        if(par[x][i] != par[y][i]){
            x = par[x][i];
            y = par[y][i];
        }
    }
    if(x == y) return x;
    return par[x][0];
}

void dfs(int pos, int pa){
    dfn[pos] = ++p0;
    tra[dfn[pos]] = pos;
    par[pos][0] = pa;
    dep[pos] = dep[pa] + 1;
    for (int i=1; i<17; i++) {
        par[pos][i] = par[par[pos][i-1]][i-1];
    }
    for (auto &x : graph[pos]){
        if(x == pa) continue;
        dfs(x,pos);
        sz[pos] += sz[x];
    }
    sz[pos]++;
}

void hld(int pos){
    comp[pos] = piv;
    cnum[pos] = ++csize[piv];
    int pmax = -1, vmax = -1;
    for (int i=0; i<graph[pos].size(); i++) {
        if(graph[pos][i] == par[pos][0]) continue;
        if(vmax < sz[graph[pos][i]]){
            vmax = sz[graph[pos][i]];
            pmax = i;
        }
    }
    if(pmax == -1) return;
    son[pos] = graph[pos][pmax];
    hld(graph[pos][pmax]);
    for (int i=0; i<graph[pos].size(); i++) {
        if(graph[pos][i] == par[pos][0] || i == pmax) continue;
        piv++;
        chead[piv] = graph[pos][i];
        hld(graph[pos][i]);
    }
}

int dp[100005], sum[100005];
int mark[100005];
vector<int> psum[100005];

int getsum(int num, int s, int e){
    if(s > e) return 0;
    return psum[num][s] - psum[num][e+1];
}

int f(int x, int y, int l){
    int ret = 0;
    while (comp[x] != comp[l]) {
        ret += getsum(comp[x],1,cnum[x]);
        x = par[chead[comp[x]]][0];
    }
    ret += getsum(comp[l],cnum[l]+1,cnum[x]);
    while (comp[y] != comp[l]) {
        ret += getsum(comp[y],1,cnum[y]);
        y = par[chead[comp[y]]][0];
    }
    ret += getsum(comp[l],cnum[l]+1,cnum[y]);
    ret += sum[l];
    return ret;
}

void solve(){
    for (int i=n; i; i--) {
        int pos = tra[i];
        for (auto &j : graph[pos]){
            if(j == par[pos][0]) continue;
            sum[pos] += dp[j];
        }
        int ret = sum[pos];
        for (auto &j : paths[pos]){
            ret = max(ret,f(j.s,j.e,pos) + j.cost);
        }
        dp[pos] = ret;
        ret = sum[pos] - dp[pos];
        psum[comp[pos]][cnum[pos]] = psum[comp[pos]][cnum[pos]+1] + ret;
    }
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        int x, y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1,0);
    scanf("%d",&m);
    for (int i=0; i<m; i++) {
        int x,y,c;
        scanf("%d %d %d",&x,&y,&c);
        int l = lca(x,y);
        paths[l].push_back({c,x,y});
    }
    piv = 1;
    hld(1);
    for (int i=1; i<=piv; i++) {
        psum[i].resize(csize[i] + 2);
    }
    solve();
    printf("%d",dp[1]);
}