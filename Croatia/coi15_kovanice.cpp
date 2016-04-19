#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
 
int n, m, v;
 
struct disj{
    int pa[300005], size[300005];
    void init(int n){
        for(int i=1; i<=n; i++) pa[i] = i, size[i] = 1;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    int getsize(int x){
        return size[find(x)];
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p; size[p] += size[q];
        return 1;
    }
}disj;
 
vector<pi> edgs;
vector<int> g1[300005], g2[300005], g3[300005];
 
int piv;
int comp[300005];
int ret[300005];
 
void dfs(int x, int p){
    if(comp[x]) return;
    comp[x] = p;
    for(auto &i : g1[x]){
        dfs(i, p);
    }
}
 
vector<pi> cnd;
int dp1[300005], dp2[300005];
 
int f(int x){
    if(~dp1[x]) return dp1[x];
    int ret = 0;
    for(auto &i : g2[x]){
        ret = max(ret, f(i));
    }
    return dp1[x] = ret + 1;
}
 
int g(int x){
    if(~dp2[x]) return dp2[x];
    int ret = 0;
    for(auto &i : g3[x]){
        ret = max(ret, g(i));
    }
    return dp2[x] = ret + 1;
}
 
void solve(int s, int e){
    for(int i=s; i<=e; i++){
        int t = cnd[i].second;
        int p1 = f(t), p2 = g(t);
        if(p1 + p2 == n+1) ret[t] = p2;
        else ret[t] = -1;
    }
}
 
int main(){
    scanf("%d %d %d",&n,&m,&v);
    disj.init(m);
    for(int i=0; i<v; i++){
        int a, b;
        char c;
        scanf("%d%c%d",&a,&c,&b);
        if(c == '='){
            g1[a].push_back(b);
            g1[b].push_back(a);
        }
        else{
            edgs.emplace_back(a, b);
        }
    }
    for(int i=1; i<=m; i++){
        if(!comp[i]) dfs(i, ++piv);
    }
    for(auto &i : edgs){
        i.first = comp[i.first];
        i.second = comp[i.second];
    }
    sort(edgs.begin(), edgs.end());
    edgs.resize(unique(edgs.begin(), edgs.end()) - edgs.begin());
    for(auto &i : edgs){
        g2[i.first].push_back(i.second);
        g3[i.second].push_back(i.first);
        disj.uni(i.first, i.second);
    }
    for(int i=1; i<=piv; i++){
        cnd.push_back(pi(disj.find(i), i));
    }
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    sort(cnd.begin(), cnd.end());
    for(int i=0; i<cnd.size();){
        int e = i;
        while(e < cnd.size() && cnd[i].first == cnd[e].first) e++;
        solve(i, e-1);
        i = e;
    }
    for(int i=1; i<=m; i++){
        if(ret[comp[i]] == -1){
            puts("?");
        }
        else{
            printf("K%d\n",ret[comp[i]]);
        }
    }
}