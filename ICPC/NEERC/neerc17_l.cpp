#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int inf = 2e9 + 100;
typedef pair<int, int> pi;

int n, m, dep[MAXN], par[17][MAXN], din[MAXN], dout[MAXN], piv;
vector<int> gph[MAXN];
pi a[MAXN];
int cnt[MAXN], pth[MAXN];

void dfs(int x, int p){
    din[x] = ++piv;
    for(auto &i : gph[x]){
        if(i == p) continue;
        dep[i] = dep[x] + 1;
        par[0][i] = x;
        dfs(i, x);
    }
    dout[x] = piv;
}

void dfs2(int x, int p){
    for(auto &i : gph[x]){
        if(i == p) continue;
        pth[i] += pth[x];
        dfs2(i, x);
        cnt[x] += cnt[i];
    }
}

int lca(int s, int e){
    if(dep[s] < dep[e]) swap(s, e);
    int dx = dep[s] - dep[e];
    for(int i=0; i<17; i++){
        if((dx >> i) & 1) s = par[i][s];
    }
    for(int i=16; i>=0; i--){
        if(par[i][s] != par[i][e]){
            s = par[i][s];
            e = par[i][e];
        }
    }
    if(s != e)return par[0][s];
    return s;
}

struct bit{
    int tree[MAXN];
    void clear(){
        memset(tree, 0, sizeof(tree));
    }
    void add(int x, int v){
        while(x <= n){
            tree[x] += v;
            x += x & -x;
        }
    }
    int query(int x){
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bit;

struct rect{
    int sx, ex, sy, ey, idx;
};

struct event{
    int pos, sgn, idx;
};

struct ievent{
    int s, e, x;
};

vector<ievent> ev2[MAXN];
vector<event> ev[MAXN];
vector<pi> pnt[MAXN];
int l[MAXN], ans[MAXN];

void solve1(vector<rect> &r){
    for(int i=0; i<=n+1; i++) ev[i].clear();
    for(auto &i : r){
        ev[i.sx-1].push_back({i.sy-1, 1, i.idx});
        ev[i.sx-1].push_back({i.ey, -1, i.idx});
        ev[i.ex].push_back({i.sy-1, -1, i.idx});
        ev[i.ex].push_back({i.ey, 1, i.idx});
    }
    bit.clear();
    for(int i=1; i<=n; i++){
        for(auto &j : pnt[i]) bit.add(j.first, 1);
        for(auto &j : ev[i]) ans[j.idx] += bit.query(j.pos) * j.sgn;
    }
}

void solve2(vector<rect> &r){
    for(auto &i : r){
        ev2[i.sx].push_back({i.sy, i.ey, 1});
        ev2[i.ex+1].push_back({i.sy, i.ey, -1});
    }
    bit.clear();
    for(int i=1; i<=n; i++){
        for(auto &j : ev2[i]){
            bit.add(j.s, j.x);
            bit.add(j.e+1, -j.x);
        }
        for(auto &j : pnt[i]){
            ans[j.second] += bit.query(j.first);
        }
    }
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<n; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    dfs(1, 0);
    for(int i=1; i<17; i++){
        for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
    }
    set<pi> s;
    for(int i=0; i<m; i++){
        int x, y;
        scanf("%d %d",&x,&y);
        if(x < y) swap(x, y);
        if(x == y) continue;
        s.insert(pi(x, y));
    }
    if(s.empty()){
        puts("Yes");
        return 0;
    }
    m = 0;
    for(auto &i : s){
        a[m] = i;
        l[m] = lca(i.first, i.second);
        cnt[l[m]]++;
        pth[l[m]]++;
        m++;
    }
    for(int i=0; i<m; i++){
        if(din[a[i].first] > din[a[i].second]) swap(a[i].first, a[i].second);
        pnt[din[a[i].first]].emplace_back(din[a[i].second], i);
    }
    dfs2(1, 0);
    for(int i=2; i<=n; i++){
        gph[i].erase(find(gph[i].begin(), gph[i].end(), par[0][i]));
    }
    vector<rect> re1, re2;
    for(int i=0; i<m; i++){
        ans[i] += cnt[l[i]] - (pth[a[i].first] + pth[a[i].second] - pth[l[i]] - pth[par[0][l[i]]]);
        if(l[i] == a[i].first){
            auto it = --upper_bound(gph[l[i]].begin(), gph[l[i]].end(), a[i].second, [&](const int &x, const int &y){
                return din[x] < din[y];
            });
            re1.push_back({1, din[*it]-1, din[a[i].second], dout[a[i].second], i});
            re1.push_back({din[a[i].second], dout[a[i].second], dout[*it]+1, n, i});
        }
        else{
            re1.push_back({din[a[i].first], dout[a[i].first], din[a[i].second], dout[a[i].second], i});
        }
        re2.push_back({1, din[l[i]] - 1, 1, din[l[i]] - 1, i});
        re2.push_back({1, din[l[i]] - 1, dout[l[i]] + 1, n, i});
        re2.push_back({dout[l[i]] + 1, n, dout[l[i]] + 1, n, i});
    }
    solve2(re1);
    solve1(re1);
    solve1(re2);
    for(int i=0; i<m; i++){
        if(ans[i] != m+1){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
}