#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct disj{
    int pa[100005], sz[100005];
    void init(int n){
        for(int i=1; i<=n; i++) pa[i] = i, sz[i] = 1;
    }
    int find(int x){
        if(pa[x] == x) return x;
        return pa[x] = find(pa[x]);
    }
    int size(int x){
        return sz[find(x)];
    }
    int uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        sz[p] += sz[q];
        return 1;
    }
}disj;

bool vis[100005];
int n,m;
vector<int> g[100005], ng[100005];
queue<int> q;

int main(){
    scanf("%d %d",&n,&m);
    disj.init(n);
    for (int i=0; i<m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        g[x].push_back(y);
    }
    for (int i=1; i<=n; i++) {
        for (int j=0; j+1<g[i].size(); j++) {
            disj.uni(g[i][j],g[i][j+1]);
        }
    }
    for (int i=1; i<=n; i++) {
        int pos = i;
        while (!vis[pos] && disj.size(pos) != 1) {
            vis[pos] = 1;
            if(!g[pos].empty()){
                disj.uni(g[pos][0],pos);
                pos = g[pos][0];
            }
        }
    }
    long long ret = 0;
    memset(vis,0,sizeof(vis));
    for (int i=1; i<=n; i++) {
        if(!vis[disj.find(i)]){
            vis[disj.find(i)] = 1;
            ret += 1ll * disj.size(i) * (disj.size(i) - 1);
        }
    }
    for (int i=1; i<=n; i++) {
        for (int &j : g[i]){
            if(disj.find(i) != disj.find(j)) ret++;
        }
    }
    printf("%lld",ret);
}