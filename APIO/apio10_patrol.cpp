#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
vector<int> graph[100005];
 
int n,k;
 
int dfn[100005], sz[100005], loc[100005], par[100005], piv;
int dp_long[100005], dp_diam[100005], pf_diam[100005], up_long[100005], sub_diam[100005];
 
int dfs(int x, int pa){
    par[x] = pa;
    dfn[x] = ++piv;
    loc[dfn[x]] = x;
    sz[x] = 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        sz[x] += dfs(graph[x][i],x);
    }
    return sz[x];
}
 
int sol[100005], size;
 
void solve(int x, int pa){
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        solve(graph[x][i],x);
    }
    size = 0;
    for (int i=0; i<graph[x].size(); i++){
        if(graph[x][i] == pa) continue;
        sol[size++] = dp_long[graph[x][i]] + 1;
    }
    if(size == 0) return;
    if(size == 1){
        dp_diam[x] = dp_long[x] = sol[0];
        return;
    }
    swap(*max_element(sol,sol + size),sol[0]);
    swap(*max_element(sol+1,sol + size),sol[1]);
    dp_long[x] = sol[0];
    dp_diam[x] = sol[0] + sol[1];
}
 
int ans2;
 
int best[100005][4];
 
void solve2(int x, int pa){
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        solve2(graph[x][i],x);
    }
    size = 0;
    sub_diam[x] = dp_diam[x];
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        sub_diam[x] = max(sub_diam[x],sub_diam[graph[x][i]]);
        sol[size++] = dp_long[graph[x][i]] + 1;
    }
    sol[size++] = up_long[x];
    for (int i=0; i<size && i<4; i++) {
        swap(*max_element(sol+i,sol + size),sol[i]);
    }
    int ret = 0;
    for (int i=0; i<4 && i<size; i++) {
        best[x][i] = sol[i];
        ret += sol[i];
    }
    ans2 = max(ans2,ret);
}
 
int main(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<n-1; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    solve(1,0);
    if(k == 1){
        printf("%d",2 * n - 1 - *max_element(dp_diam+1,dp_diam+n+1));
        return 0;
    }
    int ret = 0;
    dfs(1,0);
    for (int i=n; i; i--) {
        pf_diam[i] = max(pf_diam[i+1],dp_diam[loc[i]]);
        ret = max(ret,dp_diam[loc[i]] + pf_diam[i + sz[loc[i]]]);
    }
    for (int i=1; i<=n; i++) {
        int ret = 0;
        if(i == 1) continue;
        for (int j=0; j<graph[par[i]].size(); j++) {
            int pos = graph[par[i]][j];
            if(pos == i || pos == par[par[i]]) continue;
            ret = max(ret,dp_long[pos] + 1);
        }
        ret = max(ret,up_long[par[i]]);
        up_long[i] = ret + 1;
    }
    solve2(1,0);
    ret = max(ret,ans2);
    for (int i=1; i<=n; i++) {
        if(i == 1){
            ret = max(ret,sub_diam[i]);
            continue;
        }
        int tmp = sub_diam[i];
        int pivot = dp_long[i] + 1;
        for (int j=0; j<3; j++) {
            if(j == 2 && pivot != -1) break;
            if(best[par[i]][j] == pivot) pivot = -1;
            else tmp += best[par[i]][j];
        }
        ret = max(ret,tmp);
    }
    printf("%d",2 * n - ret);
}