#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 20005;

struct disj{
    int pa[MAXN], sz[MAXN];
    void init(int n){
        iota(pa, pa + n + 1, 0);
        fill(sz, sz + n + 1, 1);
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p); q = find(q);
        if(p == q) return 0;
        pa[q] = p; sz[p] += sz[q];
        return 1;
    }
    int getsize(int x){
        return sz[find(x)];
    }
}disj;

vector<pi> gph[MAXN];
int n, m;

int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        gph[i].push_back(pi((i + 1) % n, i * 2));
        gph[(i + 1) % n].push_back(pi(i, i * 2 + 1));
    }
    for(int i=0; i<m; i++){
        int s, e; cin >> s >> e;
        s--, e--;
        gph[s].push_back(pi(e, (i + n) * 2));
        gph[e].push_back(pi(s, (i + n) * 2 + 1));
    }
    disj.init(2 * (n + m));
    for(int i=0; i<n; i++){
        sort(gph[i].begin(), gph[i].end(), [&](const pi &a, const pi &b){
            int p = (a.first + n - i) % n;
            int q = (b.first + n - i) % n;
            return p < q;
        });
        for(int j=0; j<gph[i].size(); j++){
            disj.uni(gph[i][j].second, gph[i][(j+1)%gph[i].size()].second ^ 1);
        }
    }
    int ans = 0;
    for(int i=0; i<2*n+2*m; i++){
        if(disj.getsize(i) == n) continue;
        ans = max(ans, disj.getsize(i));
    }
    if(ans == 0) ans = n;
    cout << ans << endl;
}

