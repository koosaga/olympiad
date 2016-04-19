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

struct query{
    int type, a, b, time;
};

vector<query> v;

struct disj{
    int pa[30005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        return 1;
    }
}disj;

int n, q, a[30005];
int type[300005], ret[300005];

vector<int> graph[30005];
int dfn[30005], size[30005], p;
int par[15][30005], dep[30005];

int lca(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    int dx = dep[b] - dep[a];
    for(int i=0; i<15; i++){
        if((dx >> i) & 1) b = par[i][b];
    }
    for(int i=14; i>=0; i--){
        if(par[i][a] != par[i][b]){
            a = par[i][a];
            b = par[i][b];
        }
    }
    if(a == b) return a;
    return par[0][a];
}

int dfs(int x, int pa){
    dfn[x] = ++p;
    size[x] = 1;
    par[0][x] = pa;
    for(int i=1; i<15; i++){
        par[i][x] = par[i-1][par[i-1][x]];
    }
    for(auto &i : graph[x]){
        if(i == pa) continue;
        dep[i] = dep[x] + 1;
        size[x] += dfs(i, x);
    }
    return size[x];
}

struct seg{
    int tree[132000], lazy[132000];
    void lazydown(int p, int ps, int pe){
        int pm = (ps + pe) / 2;
        tree[2*p] += (pm - ps + 1) * lazy[p];
        tree[2*p+1] += (pe - pm) * lazy[p];
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            lazy[p] += v;
            tree[p] += v * (pe - ps + 1);
            return;
        }
        lazydown(p, ps, pe);
        int pm = (ps + pe) / 2;
        add(s, e, ps, pm, 2*p, v);
        add(s, e, pm+1, pe, 2*p+1, v);
        tree[p] = tree[2*p] + tree[2*p+1];
    }
    int query(int pos, int ps, int pe, int p){
        if(pos == 0) return 0;
        if(ps == pe) return tree[p];
        int pm = (ps + pe) / 2;
        lazydown(p, ps, pe);
        if(pos <= pm) return query(pos, ps, pm, 2*p);
        return query(pos, pm+1, pe, 2*p+1);
    }
}seg;

int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    disj.init(n);
    scanf("%d",&q);
    for(int i=0; i<q; i++){
        char str[20];
        int a, b;
        scanf("%s %d %d",str, &a, &b);
        if(*str == 'b'){
            type[i] = 1;
            if(disj.uni(a, b)){
                graph[a].push_back(b);
                graph[b].push_back(a);
                ret[i] = 1;
            }
        }
        if(*str == 'p'){
            type[i] = 2;
            v.push_back({2, a, b, i});
        }
        if(*str == 'e'){
            type[i] = 3;
            if(disj.find(a) != disj.find(b)){
                ret[i] = -1;
            }
            else{
                v.push_back({3, a, b, i});
            }
        }
    }
    for(int i=2; i<=n; i++){
        if(disj.uni(1, i)){
            graph[1].push_back(i);
            graph[i].push_back(1);
        }
    }
    dfs(1, 0);
    for(int i=1; i<=n; i++){
        seg.add(dfn[i], dfn[i] + size[i] - 1, 1, n, 1, a[i]);
    }
    for(auto &i : v){
        if(i.type == 2){
            seg.add(dfn[i.a], dfn[i.a] + size[i.a] - 1, 1, n, 1, i.b - a[i.a]);
            a[i.a] = i.b;
        }
        else if(i.type == 3){
            int l = lca(i.a, i.b);
            int val = seg.query(dfn[i.a], 1, n, 1) 
            + seg.query(dfn[i.b], 1, n, 1)
            - seg.query(dfn[par[0][l]], 1, n, 1)
            - seg.query(dfn[l], 1, n, 1);
            ret[i.time] = val;
        }
    }
    for(int i=0; i<q; i++){
        if(type[i] == 1){
            puts(ret[i] ? "yes" : "no");
        }
        else if(type[i] == 3){
            if(ret[i] == -1) puts("impossible");
            else printf("%d\n",ret[i]);
        }
    }
}
