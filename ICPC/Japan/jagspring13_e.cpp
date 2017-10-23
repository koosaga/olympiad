#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct edge{int s,e,x,num;}a[300005];
bool cmp(edge a, edge b){return a.x < b.x;}

struct disj{
    int pa[100005], r[100005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        if(pa[x] == x) return x;
        return pa[x] = find(pa[x]);
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        if(r[p] < r[q]) pa[q] = p;
        else pa[p] = q;
        if(r[p] == r[q]) r[p]++;
        return 1;
    }
}disj;

vector<edge> tree;
vector<edge> not_tree;
vector<int> graph[100005];

int n,m;
long long ret[300005];

int pa[100005][17], dep[100005], sz[100005];
int root_val[100005], nxt[100005];

int dfs(int x, int par, int depth){
    pa[x][0] = nxt[x] = par;
    dep[x] = depth;
    for (int i=1; i<=16; i++) {
        pa[x][i] = pa[pa[x][i-1]][i-1];
    }
    int r = 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == par) continue;
        r += dfs(graph[x][i],x,depth+1);
    }
    return sz[x] = r;
}

int lca(int s, int e){
    if(dep[s] > dep[e]) swap(s,e);
    int piv = dep[e] - dep[s];
    int ps = s;
    int pe = e;
    for (int i=0; (1<<i) <= piv; i++) {
        if(piv & (1<<i)){
            pe = pa[pe][i];
        }
    }
    for (int i=16; i>=0; i--) {
        if(pa[ps][i] == 0) continue;
        if(pa[ps][i] != pa[pe][i]){
            ps = pa[ps][i];
            pe = pa[pe][i];
        }
    }
    if(ps != pe){
        ps = pa[ps][0], pe = pa[pe][0];
    }
    return ps;
}

int paint(int s, int e, int x){
    if(dep[s] <= dep[e]) return s;
    if(!root_val[s]) root_val[s] = x;
    return nxt[s] = paint(nxt[s],e,x);
}

void solve(){
    long long mst = 0;
    for (int i=0; i<m; i++) {
        if(disj.uni(a[i].s,a[i].e)) {
            tree.push_back(a[i]);
            graph[a[i].s].push_back(a[i].e);
            graph[a[i].e].push_back(a[i].s);
            mst += a[i].x;
        }
        else not_tree.push_back(a[i]);
    }
    if(tree.size() != n-1){
        for (int i=0; i<m; i++) {
            ret[i] = -1;
        }
        return;
    }
    dfs(1,0,0);
    for (int i=0; i<not_tree.size(); i++) {
        ret[not_tree[i].num] = mst;
        paint(not_tree[i].s,not_tree[i].e,not_tree[i].x + 1);
        int s = not_tree[i].s;
        int e = not_tree[i].e;
        int x = not_tree[i].x + 1;
        int l = lca(s,e);
        paint(s,l,x);
        paint(e,l,x);
    }
    for (int i=0; i<tree.size(); i++) {
        if(pa[tree[i].e][0] != tree[i].s){
            swap(tree[i].s,tree[i].e);
        }
        int qr = root_val[tree[i].e];
        if(qr == 0) ret[tree[i].num] = -1;
        else ret[tree[i].num] = mst - tree[i].x + qr - 1;
    }
}

int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
        a[i].num = i;
    }
    disj.init(n);
    sort(a,a+m,cmp);
    solve();
    for (int i=0; i<m; i++) {
        printf("%lld\n",ret[i]);
    }
}