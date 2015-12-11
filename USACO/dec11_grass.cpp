#include <cstdio>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
int n;
vector<int> graph[100005];
int depth[100005];
int pa[100005][17];
int sz[100005];
 
int comp;
int chead[100005], cnum[100005], cpos[100005], csz[100005];
 
struct node{
    node() : ls(NULL), rs(NULL), sum(0ll), lazy(0) {}
    node *ls, *rs;
    long long sum;
    int lazy;
}*root[100005];
 
void lazydown(node* p, int ps, int pe){
    if(ps == pe) return;
    int pm = (ps+pe)/2;
    if(!p->ls) p->ls = new node();
    if(!p->rs) p->rs = new node();
    p->ls->lazy += p->lazy;
    p->rs->lazy += p->lazy;
    p->ls->sum += 1ll * (p->lazy) * (pm - ps + 1);
    p->rs->sum += 1ll * (p->lazy) * (pe - pm);
    p->lazy = 0;
}
 
void add(int s, int e, int ps, int pe, node* p){
    if(e < ps || pe < s) return;
    if(s <= ps && pe <= e){
        p->lazy++;
        p->sum += (pe - ps + 1);
        return;
    }
    lazydown(p,ps,pe);
    int pm = (ps+pe)/2;
    add(s,e,ps,pm,p->ls);
    add(s,e,pm+1,pe,p->rs);
    p->sum = p->ls->sum + p->rs->sum;
}
 
long long q(int s, int e, int ps, int pe, node* p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return p->sum;
    lazydown(p,ps,pe);
    int pm = (ps+pe)/2;
    return q(s,e,ps,pm,p->ls) + q(s,e,pm+1,pe,p->rs);
}
 
int dfs(int x, int p, int d){
    if(x != 1){
        pa[x][0] = p;
        depth[x] = d;
        for (int i=1; (1<<i) <= d; i++) {
            pa[x][i] = pa[pa[x][i-1]][i-1];
        }
    }
    sz[x] = 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == p) continue;
        sz[x] += dfs(graph[x][i],x,d+1);
    }
    return sz[x];
}
 
int lca(int a, int b){
    if(depth[b] < depth[a]) swap(a,b);
    int diff = depth[b] - depth[a];
    for (int i=0; diff; i++) {
        if(diff&1){
            b = pa[b][i];
        }
        diff >>= 1;
    }
    for (int i=16; i>=0; i--) {
        if(pa[a][i] != pa[b][i]){
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    if(a != b) return pa[a][0];
    return a;
}
 
void hld(int p, int pa){
    if(csz[comp] == 0) chead[comp] = p;
    cnum[p] = comp;
    csz[comp]++;
    cpos[p] = csz[comp];
    int hlp = -1, hlv = -1;
    for (int i=0; i<graph[p].size(); i++) {
        if(graph[p][i] == pa) continue;
        if(hlv < sz[graph[p][i]]){
            hlv = sz[graph[p][i]];
            hlp = graph[p][i];
        }
    }
    if(hlp == -1) return;
    hld(hlp,p);
    for (int i=0; i<graph[p].size(); i++) {
        if(graph[p][i] == pa || graph[p][i] == hlp) continue;
        comp++;
        hld(graph[p][i],p);
    }
}
 
void paint(int s, int l){
    while (cnum[s] != cnum[l]) {
        int comp = cnum[s];
        add(1,cpos[s],1,csz[comp],root[comp]);
        s = pa[chead[comp]][0];
    }
    if(cnum[s] == cnum[l]){
        int comp = cnum[s];
        add(cpos[l]+1,cpos[s],1,csz[comp],root[comp]);
    }
}
 
long long query(int s, int l){
    long long ret = 0;
    while (cnum[s] != cnum[l]) {
        int comp = cnum[s];
        ret += q(1,cpos[s],1,csz[comp],root[comp]);
        s = pa[chead[comp]][0];
    }
    if(cnum[s] == cnum[l]){
        int comp = cnum[s];
        ret += q(cpos[l]+1,cpos[s],1,csz[comp],root[comp]);
    }
    return ret;
}
 
int main(){
    int q;
    scanf("%d %d",&n,&q);
    for (int i=0; i<n-1; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1,0,0);
    hld(1,0);
    for (int i=0; i<=comp; i++) {
        root[i] = new node();
    }
    while (q--) {
        char str[10];
        int p,q;
        scanf("%s %d %d",str,&p,&q);
        if(str[0] == 'Q'){
            int l = lca(p,q);
            printf("%lld\n",query(p,l) + query(q,l));
        }
        else{
            int l = lca(p,q);
            paint(p,l);
            paint(q,l);
        }
    }
}