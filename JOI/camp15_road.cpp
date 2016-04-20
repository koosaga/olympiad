#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> graph[100005];

struct disj{
    int pa[100005];
    void init(int n){
        for (int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        return 1;
    }
}disj;

int n, q;

int ans[300005];
struct road_dev{int t, s, e;}qr[300005];

int size[100005];
int comp[100005], cnum[100005], head[100005], csize[100005], piv;
int par[100005][17], dep[100005];

int dfs(int x, int pa){
    size[x] = 1;
    par[x][0] = pa;
    dep[x] = dep[pa] + 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        size[x] += dfs(graph[x][i],x);
    }
    return size[x];
}

void dfs2(int x, int pa){
    comp[x] = piv;
    cnum[x] = ++csize[piv];
    int maxv = -1, maxp = -1;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        if(size[graph[x][i]] > maxv){
            maxv = size[graph[x][i]];
            maxp = i;
        }
    }
    if(maxp == -1) return;
    dfs2(graph[x][maxp],x);
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa || i == maxp) continue;
        piv++;
        head[piv] = graph[x][i];
        dfs2(graph[x][i],x);
    }
}

struct node{
    node *ls, *rs;
    int sum, lazy;
    node(){
        ls = rs = NULL;
        sum = lazy = 0;
    }
}*root[100005];

void lazydown(int ps, int pe, node* p){
    if(p->lazy == 0) return;
    int pm = (ps + pe) / 2;
    p->ls->sum = pm - ps + 1;
    p->rs->sum = pe - pm;
    p->ls->lazy = p->rs->lazy = 1;
    p->lazy = 0;
}

void add(int s, int e, int ps, int pe, node* p){
    if(e < ps || pe < s) return;
    if(s <= ps && pe <= e){
        p->sum = pe - ps + 1;
        p->lazy = 1;
        return;
    }
    int pm = (ps + pe) / 2;
    if(!p->ls) p->ls = new node();
    if(!p->rs) p->rs = new node();
    lazydown(ps,pe,p);
    add(s,e,ps,pm,p->ls);
    add(s,e,pm+1,pe,p->rs);
    p->sum = p->ls->sum + p->rs->sum;
}

int sum(int s, int e, int ps, int pe, node *p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return p->sum;
    int pm = (ps + pe) / 2;
    if(!p->ls) p->ls = new node();
    if(!p->rs) p->rs = new node();
    lazydown(ps,pe,p);
    return sum(s,e,ps,pm,p->ls) + sum(s,e,pm+1,pe,p->rs);
}

int LCA(int x, int y){
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

int dist(int x, int y){
    return dep[x] + dep[y] - 2 * dep[LCA(x,y)];
}

int query(int x){
    if(x == 0) return 0;
    int ret = 0;
    while (x) {
        ret += sum(1,cnum[x],1,csize[comp[x]],root[comp[x]]);
        x = par[head[comp[x]]][0];
    }
    return ret;
}

void fill(int x, int y){
    int l = LCA(x,y);
    while (comp[x] != comp[l]) {
        add(1,cnum[x],1,csize[comp[x]],root[comp[x]]);
        x = par[head[comp[x]]][0];
    }
    while (comp[y] != comp[l]) {
        add(1,cnum[y],1,csize[comp[y]],root[comp[y]]);
        y = par[head[comp[y]]][0];
    }
    add(cnum[l]+1,cnum[y],1,csize[comp[l]],root[comp[l]]);
    add(cnum[l]+1,cnum[x],1,csize[comp[l]],root[comp[l]]);
}

int main(){
    scanf("%d %d",&n,&q);
    disj.init(n);
    for (int i=0; i<q; i++) {
        scanf("%d %d %d",&qr[i].t,&qr[i].s,&qr[i].e);
        if(qr[i].t == 1){
            if(disj.uni(qr[i].s,qr[i].e)){
                graph[qr[i].s].push_back(qr[i].e);
                graph[qr[i].e].push_back(qr[i].s);
                qr[i].t = -1;
            }
        }
        else if(qr[i].t == 2){
            if(disj.find(qr[i].s) != disj.find(qr[i].e)){
                ans[i] = -1;
                qr[i].t = -2;
            }
        }
    }
    for (int i=2; i<=n; i++) {
        if(disj.uni(1,i)){
            graph[1].push_back(i);
            graph[i].push_back(1);
        }
    }
    head[1] = 1;
    dep[0] = -1;
    dfs(1,0);
    piv++;
    dfs2(1,0);
    for (int j=1; j<17; j++) {
        for (int i=1; i<=n; i++) {
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
    for (int i=1; i<=piv; i++) {
        root[i] = new node();
    }
    for (int i=0; i<q; i++) {
        if(qr[i].t == -1 || qr[i].t == -2) continue;
        if(qr[i].t == 1) fill(qr[i].s,qr[i].e);
        else{
            ans[i] = dist(qr[i].s,qr[i].e)
            - query(qr[i].s) - query(qr[i].e)
            + 2 * query(LCA(qr[i].s,qr[i].e));
        }
    }
    for (int i=0; i<q; i++) {
        if(qr[i].t == 2 || qr[i].t == -2){
            printf("%d\n",ans[i]);
        }
    }
}