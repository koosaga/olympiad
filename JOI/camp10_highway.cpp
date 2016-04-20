#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

pi edg[100005];
int cst_up[100005], cst_dn[100005];

vector<int> graph[100005];

int dfn[100005], piv;
int pa[100005][17], dep[100005], sz[100005];
int n;

int dfs(int x, int p, int d){
    dfn[x] = ++piv;
    pa[x][0] = p;
    dep[x] = d;
    int ret = 1;
    for (int i=1; i<=16; i++) {
        pa[x][i] = pa[pa[x][i-1]][i-1];
    }
    for (auto &i : graph[x]){
        if(p != i) ret += dfs(i,x,d+1);
    }
    return sz[x] = ret;
}

int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x,y);
    int diff = dep[x] - dep[y], piv = 0;
    while (diff) {
        if(diff&1){
            x = pa[x][piv];
        }
        piv++;
        diff >>= 1;
    }
    for (int i=16; i>=0; i--) {
        if(pa[x][i] != pa[y][i]){
            x = pa[x][i];
            y = pa[y][i];
        }
    }
    if(x == y) return x;
    return pa[x][0];
}

struct seg{
    int tree[270000], lazy[270000];
    void lazydown(int p, int ps, int pe){
        int pm = (ps+pe)/2;
        tree[2*p] += lazy[p] * (pm - ps + 1);
        tree[2*p+1] += lazy[p] * (pe - pm);
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += (pe - ps + 1) * v;
            lazy[p] += v;
            return;
        }
        lazydown(p,ps,pe);
        int pm = (ps+pe)/2;
        add(s,e,ps,pm,2*p,v);
        add(s,e,pm+1,pe,2*p+1,v);
    }
    int q(int s, int e, int ps, int pe, int p){
        if(e < ps || pe < s) return 0;
        if(s <= ps && pe <= e) return tree[p];
        lazydown(p,ps,pe);
        int pm = (ps+pe)/2;
        return q(s,e,ps,pm,2*p) + q(s,e,pm+1,pe,2*p+1);
    }
}up, dn;

int main(){
    int q;
    scanf("%d %d",&n,&q);
    for (int i=1; i<n; i++) {
        cst_up[i] = cst_dn[i] = 1;
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
        edg[i] = pi(x,y);
    }
    dfs(1,0,0);
    while (q--) {
        char s[10];
        scanf("%s",s);
        if(s[0] == 'I'){
            int e,p,q;
            scanf("%d %d %d",&e,&p,&q);
            int pos;
            if(dep[edg[e].first] < dep[edg[e].second]){
                swap(p,q);
                pos = edg[e].second;
            }
            else{
                pos = edg[e].first;
            }
            int tp = p, tq = q;
            p = p - cst_up[e];
            q = q - cst_dn[e];
            cst_up[e] = tp;
            cst_dn[e] = tq;
            up.add(dfn[pos],dfn[pos] + sz[pos] - 1,1,n,1,p);
            dn.add(dfn[pos],dfn[pos] + sz[pos] - 1,1,n,1,q);
        }
        else{
            int s,e;
            scanf("%d %d",&s,&e);
            int l = lca(s,e);
            int ret = dep[e] + dep[s] - 2 * dep[l];
            s = dfn[s];
            e = dfn[e];
            l = dfn[l];
            ret += up.q(s,s,1,n,1) - up.q(l,l,1,n,1);
            ret += dn.q(e,e,1,n,1) - dn.q(l,l,1,n,1);
            printf("%d\n",ret);
        }
    }
}