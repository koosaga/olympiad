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
typedef pair<int, int> pi;
 
int n, m;
vector<pi> gph[100005];
int dfn[100005], low[100005], piv;
 
void dfs(int x, int p){
    dfn[x] = low[x] = ++piv;
    int child = 0;
    for(auto &i : gph[x]){
        if(p == i.first) continue;
        if(!dfn[i.second]){
            child++;
            dfs(i.second, i.first);
            low[x] = min(low[x], low[i.second]);
        }
        else{
            low[x] = min(low[x], dfn[i.second]);
        }
    }
}
 
int col[100005], cpiv;
bool vis[100005];
 
bool cutedge(int x, int y){
    if(dfn[x] < dfn[y]) swap(x, y);
    return low[x] > dfn[y];
}
 
void color(int x, int c){
    col[x] = c;
    vis[x] = 1;
    for(auto &i : gph[x]){
        if(vis[i.second]) continue;
        if(cutedge(x, i.second)){
            color(i.second, ++cpiv);
        }
        else{
            color(i.second, c);
        }
    }
}
 
vector<int> bcc[100005];
int colp[100005], cpiv2;
 
void color2(int x, int c){
    if(c > 0) bcc[x].push_back(c);
    for(auto &i : gph[x]){
        if(bcc[i.second].size()) continue;
        if(low[i.second] >= dfn[x]){
            cpiv2++;
            bcc[x].push_back(cpiv2);
            colp[cpiv2] = x;
            color2(i.second, cpiv2);
        }
        else{
            color2(i.second, c);
        }
    }
}
 
vector<pi> tree[100005];
int din[100005], dout[100005], tpiv;
int par[100005], pae[100005];
 
void tdfs(int x, int p){
    din[x] = ++tpiv;
    for(auto &i : tree[x]){
        if(i.second == p) continue;
        par[i.second] = x;
        pae[i.second] = i.first;
        tdfs(i.second, x);
    }
    dout[x] = ++tpiv;
}
 
bool son(int a, int b){
    return din[a] <= din[b] && dout[b] <= dout[a];
}
 
bool query(int a, int b, int g1, int g2){
    g1 = col[g1];
    g2 = col[g2];
    a = col[a];
    b = col[b];
    if(g1 == g2) return 0;
    else{
        if(son(g2, g1)) swap(g1, g2);
        return son(g2, a) != son(g2, b);
    }
}
 
vector<int> tree2[200005];
int din2[200005], dout2[200005], tpiv2;
int lab[100005], dep[200005];
int spt[200005][18];
 
void tdfs2(int x, int p){
    for(int i=1; i<18; i++){
        spt[x][i] = spt[spt[x][i-1]][i-1];
    }
    din2[x] = ++tpiv2;
    for(auto &i : tree2[x]){
        if(i == p) continue;
        dep[i] = dep[x] + 1;
        spt[i][0] = x;
        tdfs2(i, x);
    }
    dout2[x] = ++tpiv2;
}
 
int lca(int s, int e){
    if(dep[e] < dep[s]) swap(s, e);
    int dx = dep[e] - dep[s];
    for(int i=0; i<=17; i++){
        if((dx >> i) & 1) e = spt[e][i];
    }
    for(int i=17; i>=0; i--){
        if(spt[s][i] != spt[e][i]){
            s = spt[s][i];
            e = spt[e][i];
        }
    }
    if(s != e) return spt[s][0];
    return s;
}
 
bool son2(int a, int b){
    return din2[a] <= din2[b] && dout2[b] <= dout2[a];
}
 
bool query2(int a, int b, int c){
    if(bcc[a].size() == 1) a = bcc[a][0];
    else a = lab[a];
    if(bcc[b].size() == 1) b = bcc[b][0];
    else b = lab[b];
    c = lab[c];
    return c == lca(a, b) || (son2(c, a) != son2(c, b));
}
 
int s[500005], e[500005];
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        scanf("%d %d",&s[i],&e[i]);
        gph[s[i]].push_back(pi(i, e[i]));
        gph[e[i]].push_back(pi(i, s[i]));
    }
    dfs(1, -1);
    color(1, ++cpiv);
    color2(1, 0);
    for(int i=1; i<=n; i++){
        if(bcc[i].size() > 1){
            lab[i] = ++cpiv2;
            for(auto &j : bcc[i]){
                tree2[j].push_back(lab[i]);
                tree2[lab[i]].push_back(j);
            }
        }
    }
    for(int i=0; i<m; i++){
        if(col[s[i]] != col[e[i]]){
            tree[col[s[i]]].push_back(pi(i, col[e[i]]));
            tree[col[e[i]]].push_back(pi(i, col[s[i]]));
        }
    }
    tdfs(1, 0);
    tdfs2(1, 0);
    int q;
    scanf("%d",&q);
    while(q--){
        int t;
        scanf("%d",&t);
        if(t == 1){
            int a, b, g1, g2;
            scanf("%d %d %d %d",&a,&b,&g1,&g2);
            puts(query(a, b, g1, g2) ? "no" : "yes");
        }
        else{
            int a, b, c;
            scanf("%d %d %d",&a,&b,&c);
            if(bcc[c].size() == 1){
                puts("yes");
                continue;
            }
            else{
                puts(query2(a, b, c) ? "no" : "yes");
            }
        }
    }
}