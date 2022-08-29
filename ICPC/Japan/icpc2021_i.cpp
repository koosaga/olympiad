#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 100005;

struct disj{
    int pa[MAXN];
    void init(int n){
        iota(pa, pa + n + 1, 0);
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p; return 1;
    }
}disj;

int sz[MAXN], par[MAXN], dep[MAXN];
int psum[MAXN], dx[MAXN];
vector<int> gph[MAXN];
vector<pi> vect;

void dfs(int x, int p){
    sz[x] = 1;
    for(auto &y : gph[x]){
        if(y != p && !sz[y]){
            dep[y] = dep[x] + 1;
            par[y] = x;
            dfs(y, x);
            sz[x] += sz[y];
        }
        else if(dep[x] < dep[y]){
            vect.emplace_back(x, y);
        }
    }
}

void dfs2(int x, int p){
    for(auto &y : gph[x]){
        if(par[y] == x){
            psum[y] = psum[x] + (sz[y] % 2 == 0);
            dfs2(y, x);
        }
    }
}

void dfs3(int x, int p){
    for(auto &y : gph[x]){
        if(par[y] == x){
            dfs3(y, x);
            dx[x] += dx[y];
        }
    }
}
int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        gph[u].push_back(v);
        gph[v].push_back(u);
    }
    dfs(0, -1);
    dfs2(0, -1);
    disj.init(n);
    for(auto &[x, y] : vect){
        if(psum[y] != psum[x]) continue;
        dx[y]++;
        dx[x]--;
        disj.uni(x, y);
    }
    dfs3(0, -1);
    for(int i = 1; i < n; i++){
        if(sz[i] % 2 && !dx[i]) disj.uni(par[i], i);
    }
    map<int, vector<int>> mp; 
    for(int i = 0; i < n; i++){
        mp[disj.find(i)].push_back(i);
    }
    cout << sz(mp) << "\n";
    for(auto &[_, x] : mp){
        assert(sz(x) % 2 == 0);
        cout << sz(x);
        for(auto &y : x) cout << " " << y;
        cout << "\n";
    }
}
