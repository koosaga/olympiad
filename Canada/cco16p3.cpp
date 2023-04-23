#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m, lmax;
vector<int> gph[100005], tree[100005];
vector<pi> edges;
int vis[100005], dx[100005], par[100005], dep[100005], instk[100005], vis2[100005];

void init(){
    edges.clear();
    for(int i=1; i<=n; i++){
        gph[i].clear();
        tree[i].clear();
        vis[i] = dx[i] = par[i] = dep[i] = vis2[i] = 0;
    }
}

void dfs1(int x, int p){
    vis[x] = 1;
    instk[x] = 1;
    for(auto &i : gph[x]){
        if(i == p) continue;
        if(vis[i]){
            if(instk[i]){
                dx[x]++;
                dx[i]--;
                lmax = max(lmax, dep[x] - dep[i] + 1);
            }
        }
        else{
            tree[x].push_back(i);
            par[i] = x;
            dep[i] = dep[x] + 1;
            dfs1(i, x);
        }
    }
    instk[x] = 0;
}

void dfs2(int x, int p){
    for(auto &i : tree[x]){
        dfs2(i, x);
        dx[x] += dx[i];
    }
}

bool solve1(){
    for(int i=1; i<=n; i++){
        if(!vis[i]) dfs1(i, -1), dfs2(i, -1);
    }
    return *max_element(dx + 2, dx + n + 1) >= 2;
}

bool solve2(){
    for(int i=1; i<=n; i++){
        if(!vis[i]) dfs1(i, -1), dfs2(i, -1);
    }
    return *max_element(dx + 2, dx + n + 1) >= 1;
}

bool solve4(){
    for(int i=1; i<=n; i++){
        if(gph[i].size() >= 3) return 1;
    }
    return 0;
}

bool solve3(){
    lmax = 0;
    if(solve1()) return 1;
    return lmax >= 4;
    return 0;
}

int dfn[1005], low[1005], piv, ban;

void dfs3(int x, int p){
    dfn[x] = low[x] = ++piv;
    for(auto &i : gph[x]){
        if(i == ban || i == p) continue;
        if(dfn[i]){
            low[x] = min(low[x], dfn[i]);
        }
        else{
            dfs3(i, x);
            low[x] = min(low[x], low[i]);
        }
    }
}

bool solve(int b, int r){
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    piv = 0;
    ban = b;
    dfs3(r, -1);
    for(int i=1; i<=n; i++){
        if(low[i] == 1 && i != r && gph[i].size() >= 3){
            if(gph[i].size() == 3 && find(gph[i].begin(), gph[i].end(), b) != gph[i].end()){
                continue;
            }
            return 1;
        }
    }
    return 0;
}

bool solve5(){
    for(int i=0; i<edges.size(); i++){
        if(solve(edges[i].first, edges[i].second)) return 1;
        if(solve(edges[i].second, edges[i].first)) return 1;
    }
    return 0;
}

int main(){
    int s, t;
    cin >> s >> t;
    while(t--){
        scanf("%d %d",&n,&m);
        for(int i=0; i<m; i++){
            int s, e;
            scanf("%d %d",&s,&e);
            gph[s].push_back(e);
            gph[e].push_back(s);
            edges.emplace_back(s, e);
        }
        if(s == 1) puts(solve1() ? "YES" : "NO");
        if(s == 2) puts(solve2() ? "YES" : "NO");
        if(s == 3) puts(solve3() ? "YES" : "NO");
        if(s == 4) puts(solve4() ? "YES" : "NO");
        if(s == 5) puts(solve5() ? "YES" : "NO");
        init();
    }
}
