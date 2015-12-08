#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
 
int n,m;
int c[100005], l[100005];
 
vector<int> graph[100005];
int sz[100005], dfn[100005], piv;
long long res;
 
int dfs(int x){
    dfn[x] = ++piv;
    int r = 1;
    for (int i=0; i<graph[x].size(); i++) {
        r += dfs(graph[x][i]);
    }
    return sz[dfn[x]] = r;
}
 
struct rmq{
    pi tree[270000];
    int lim;
    void init(int* a,int n){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[lim + dfn[i]] = pi(a[i],dfn[i]);
        }
        for(int i=lim; i; i--){
            tree[i] = max(tree[2*i],tree[2*i+1]);
        }
    }
    void add(int x, int v){
        x += lim;
        tree[x] = pi(v,x-lim);
        while(x>1){
            x >>= 1;
            tree[x] = max(tree[2*x],tree[2*x+1]);
        }
    }
    pi q(int s, int e){
        s += lim;
        e += lim;
        pi r(0,0);
        while(s < e){
            if(s%2 == 1) r = max(r,tree[s++]);
            if(e%2 == 0) r = max(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = max(r,tree[s]);
        return r;
    }
}rmq;
 
pi f(int x){
    long long cst = 0;
    int cnt = 0;
    for (int i=0; i<graph[x].size(); i++) {
        pi tmp = f(graph[x][i]);
        cst += tmp.first;
        cnt += tmp.second;
    }
    cnt++;
    cst += c[x];
    while (cst > m && cnt) {
        pi ret = rmq.q(dfn[x],dfn[x]+sz[dfn[x]]-1);
        cst -= ret.first;
        cnt--;
        rmq.add(ret.second,-1);
    }
    res = max(res,1ll * cnt * l[x]);
    return pi((int)cst,cnt);
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        int b;
        scanf("%d %d %d",&b,&c[i],&l[i]);
        if(b) graph[b].push_back(i);
    }
    dfs(1);
    rmq.init(c,n);
    f(1);
    printf("%lld",res);
}