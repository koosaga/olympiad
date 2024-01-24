#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

struct disj {
    lint pa[MAXN], rk[MAXN];
    lint up[MAXN];
    void init(int n) { iota(pa, pa + n, 0); }
    pi find(int x) {
        if (pa[x] == x)
            return pi{x, 0};
        auto g = find(pa[x]);
        return pi{g[0], g[1] + up[x]};
    }
    bool uni(int p, int q, lint d, vector<pair<lint *, lint>> &upds) {
        {
            auto [np, nd] = find(p);
            p = np;
            d += nd;
        }
        {
            auto [nq, nd] = find(q);
            q = nq;
            d -= nd;
        }
        if (p == q) {
            return d == 0;
        }
        if (rk[p] > rk[q])
            swap(p, q), d *= -1;
        upds.push_back({pa + p, pa[p]});
        upds.push_back({up + p, up[p]});
        pa[p] = q;
        up[p] = -d;
        if (rk[p] == rk[q]) {
            upds.push_back({rk + q, rk[q]});
            rk[q]++;
        }
        return true;
    }
    void rollback(vector<pair<lint *, lint>> &logs) {
        reverse(all(logs));
        for (auto &[a, b] : logs) {
            *a = b;
        }
        logs.clear();
    }
} disj;

int solve(int s, int e, vector<array<int, 3>> &edges) {
    if (s == e)
        return s;
    int m = (s + e) / 2;
    bool ok = 1;
    vector<pair<lint *, lint>> rb;
    for (int i = m + 1; i <= e; i++) {
        if (!disj.uni(edges[i][0], edges[i][1], edges[i][2], rb)) {
            ok = 0;
            break;
        }
    }
    int ret;
    if (!ok) {
        ret = -1;
    } else {
        ret = solve(s, m, edges);
    }
    disj.rollback(rb);
    if (ret == -1) {
        ok = 1;
        for (int i = s; i <= m; i++) {
            if (!disj.uni(edges[i][0], edges[i][1], edges[i][2], rb)) {

                ok = 0;
                break;
            }
        }
        if (!ok) {
            ret = -1;
        } else {
            ret = solve(m + 1, e, edges);
        }
        disj.rollback(rb);
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<array<int, 3>> edges(n);
    for (auto &[u, v, w] : edges) {
        cin >> u >> v >> w;
        u--;
        v--;
    }
    disj.init(k);
    cout << solve(0, n - 1, edges) + 1 << "\n";
}