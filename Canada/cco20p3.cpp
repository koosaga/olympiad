#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 500005;

struct edge{
    int s, e, x;
};

int n, m;
vector<int> gph[MAXN];
int par[20][MAXN], dep[MAXN];

int lca(int x, int y){
    if(dep[x] > dep[y]) swap(x, y);
    int dx = dep[y] - dep[x];
    for(int i = 0; dx; i++){
        if(dx & 1) y = par[i][y];
        dx >>= 1;
    }
    if(x == y) return x;
    for(int i = 17; i >= 0; i--){
        if(par[i][x] != par[i][y]){
            x = par[i][x];
            y = par[i][y];
        }
    }
    return par[0][x];
}

struct node{
    int lmax, rmax, opt, len;
    node():
    lmax(-1e9), rmax(-1e9), opt(-1e9), len(0) {}
    node(int x):
    lmax(x), rmax(x), opt(-1e9), len(1) {}

    node(int a, int b, int c, int e):
    lmax(a), rmax(b), opt(c), len(e) {}

    node reverse(){
        return node(rmax, lmax, opt, len);
    }
    node operator+(const node &n)const{
        return node(
            max(lmax - n.len, n.lmax),
            max(rmax, n.rmax - len),
            max({opt, n.opt, lmax + n.rmax - 1}),
            len + n.len);
    };
};

vector<int> ord;
int din[MAXN], dout[MAXN], piv;
int far[MAXN], diam[MAXN], pfar[MAXN], pdiam[MAXN];
int f[20][MAXN];
node g[20][MAXN];
vector<pi> fars[MAXN];
vector<pi> subDiams[MAXN];

int fPathMax(int x, int v){
    int ans = -1e9;
    for(int i = 0; v; i++){
        if(v & 1){
            ans = max(ans, f[i][x]);
            x = par[i][x];
        }
        v >>= 1;
    }
    return ans;
}

node gPathSum(int x, int v){
    node gs;
    for(int i = 0; v; i++){
        if(v & 1){
            gs = gs + g[i][x];
            x = par[i][x];
        }
        v >>= 1;
    }
    return gs;
}

bool in(int u, int v){
    return din[u] <= din[v] && dout[v] <= dout[u];
}

void dfs(int x, int p = -1){
    ord.push_back(x);
    din[x] = ++piv;
    for(auto &y : gph[x]){
        if(y == p) continue;
        par[0][y] = x;
        dep[y] = dep[x] + 1;
        dfs(y, x);
    }
    dout[x] = piv;
}

bool vis[MAXN];

pi dfsl(int x, int p = -1){
    pi ret(0, x);
    for(auto &y : gph[x]){
        if(y == p || vis[y]) continue;
        auto ans = dfsl(y, x);
        ans.first++;
        ret = max(ret, ans);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    vector<edge> qry;
    for(int i = 0; i < m; i++){
        int s, e, x; cin >> s >> e >> x;
        if(x == 1){
            gph[s].push_back(e);
            gph[e].push_back(s);
        }
        else{
            qry.push_back({s, e, x});
        }
    }
    dfs(0);
    for(int i = 1; i < 20; i++){
        for(int j = 0; j < n; j++){
            par[i][j] = par[i-1][par[i-1][j]];
        }
    }
    {
        reverse(all(ord));
        for(auto &i : ord){
            for(auto &j : gph[i]){
                if(j == par[0][i]) continue;
                far[i] = max(far[i], far[j] + 1);
                diam[i] = max({diam[i], diam[j], far[j] + 1});
                fars[i].emplace_back(far[j], j);
            }
            sort(all(fars[i]));
            reverse(all(fars[i]));
            if(sz(fars[i]) >= 2) diam[i] = max(diam[i], (int)fars[i][0].first + (int)fars[i][1].first + 2);
        }
        reverse(all(ord));
        for(auto &i : ord){
            if(i == 0) continue;
            for(auto &j : fars[par[0][i]]){
                if(j.second == i) continue;
                pfar[i] = j.first + 1;
                break;
            }
            fars[i].emplace_back(pfar[i], par[0][i]);
            sort(all(fars[i]));
            reverse(all(fars[i]));
        }   
        for(auto &i : ord){
            if(i == 0) continue;
            for(auto &[d, v] : subDiams[par[0][i]]){
                if(v == i) continue;
                pdiam[i] = max(pdiam[i], (int)d);
                break;
            }
            {
                int new_diam = 0;
                int cnt = 0;
                for(auto &[d, v] : fars[par[0][i]]){
                    if(v == i) continue;
                    new_diam += d + 1;
                    cnt += 1;
                    if(cnt == 2) break;
                }
                pdiam[i] = max(pdiam[i], new_diam);
            }
            for(auto &j : gph[i]){
                if(j == par[0][i]) subDiams[i].emplace_back(pdiam[i], j);
                else subDiams[i].emplace_back(diam[j], j);
            }
            sort(all(subDiams[i]));
            reverse(all(subDiams[i]));
        }
        for(int i = 0; i < n; i++){
            if(dep[i] >= 2){
                int cnt = 0;
                int gi = 0;
                for(auto &[d, v] : fars[par[0][i]]){
                    if(v == i || v == par[1][i]) continue;
                    gi = max(gi, (int)d + 1);
                    f[0][i] += d + 1;
                    cnt++;
                    if(cnt == 2) break;
                }
                for(auto &[d, v] : subDiams[par[0][i]]){
                    if(v == i || v == par[1][i]) continue;
                    f[0][i] = max(f[0][i], (int)d);
                    break;
                }
                g[0][i] = node(gi);
            }
        }
        for(int i = 1; i < 20; i++){
            for(int j = 0; j < n; j++){
                f[i][j] = max(f[i-1][j], f[i-1][par[i-1][j]]);
                g[i][j] = g[i-1][j] + g[i-1][par[i-1][j]];
            }
        }
    }
    int ans = 2 * n - 2 - diam[0];
    for(auto &x : qry){
        int l = lca(x.s, x.e);
        int plen = dep[x.s] + dep[x.e] - 2 * dep[l] + 1;
        int maxPath = -1e9;
        if(dep[x.s] >= dep[l] + 2){
            maxPath = max(maxPath, fPathMax(x.s, dep[x.s] - dep[l] - 1) - 3 + plen);
        }
        if(dep[x.e] >= dep[l] + 2){
            maxPath = max(maxPath, fPathMax(x.e, dep[x.e] - dep[l] - 1) - 3 + plen);
        }
        if(l != x.s){
            maxPath = max(maxPath, diam[x.s] - 3 + plen);
        }
        if(l != x.e){
            maxPath = max(maxPath, diam[x.e] - 3 + plen);
        }
        {
            int new_diam = 0;
            int cnt = 0;
            // passes through l
            for(auto &[d, v] : fars[l]){
                if((in(v, x.s) || in(v, x.e)) && v != par[0][l]) continue;
                new_diam += d + 1;
                cnt += 1;
                if(cnt == 2) break;
            }
            for(auto &[d, v] : subDiams[l]){
                if((in(v, x.s) || in(v, x.e)) && v != par[0][l]) continue;
                new_diam = max(new_diam, (int)d);
                break;
            }
            maxPath = max(maxPath, new_diam - 3 + plen);
        }
        // TODO: qn.
        node valup, valdown;
        if(x.s != l) valup = valup + node(far[x.s]);
        if(x.e != l) valdown = valdown + node(far[x.e]);
        if(dep[x.s] >= dep[l] + 2){
            valup = valup + gPathSum(x.s, dep[x.s] - dep[l] - 1);
        }
        if(dep[x.e] >= dep[l] + 2){
            valdown = valdown + gPathSum(x.e, dep[x.e] - dep[l] - 1);
        }
        {
            int dist = 0;
            for(auto &[d, v] : fars[l]){
                if((in(v, x.s) || in(v, x.e)) && v != par[0][l]) continue;
                dist = max(dist, (int)d + 1);
                break;
            }
            valup = valup + node(dist);
        }
        node val = valup + valdown.reverse();
        maxPath = max(maxPath, val.opt + val.len - 1);
        ans = min(ans, 2 * n - 4 + x.x - maxPath);
    }
    cout << ans << endl;
}
