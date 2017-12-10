#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;

struct disj{
    int pa[MAXN], sz[MAXN];
    void init(int n){
        for(int i=0; i<=n; i++){
            pa[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        sz[p] += sz[q];
        return 1;
    }
}disj;

int n, m;
int s[MAXN], e[MAXN], sz;
lint dep[MAXN];
vector<pi> gph[MAXN];

void dfs(int x, int p){
    for(auto &i : gph[x]){
        if(i.second == p) continue;
        dep[i.second] = dep[x] + i.first;
        dfs(i.second, x);
    }
}

int main(){
    while(true){
        scanf("%d %d",&n,&m);
        for(int i=0; i<=n; i++) gph[i].clear();
        disj.init(n);
        sz = 0;
        if(!n && !m) break;
        for(int i=0; i<m; i++){
            char buf[10];
            scanf("%s", buf);
            if(*buf == '!'){
                int a, b, w;
                scanf("%d %d %d",&a,&b,&w);
                if(disj.uni(a, b)){
                gph[a].push_back(pi(w, b));
                gph[b].push_back(pi(-w, a));
                }
            }
            else{
                int a, b;
                scanf("%d %d",&a,&b);
                s[sz] = a, e[sz] = b;
                if(disj.find(a) != disj.find(b)){
                    s[sz] = e[sz] = -1;
                }
                sz++;
            }
        }
        for(int i=2; i<=n; i++){
            if(disj.uni(1, i)){
                gph[1].push_back(pi(0, i));
                gph[i].push_back(pi(0, 1));
            }
        }
        dfs(1, -1);
        for(int i=0; i<sz; i++){
            if(s[i] == -1) puts("UNKNOWN");
            else printf("%lld\n", dep[e[i]] - dep[s[i]]); 
        }
    }
}
