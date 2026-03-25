//kuroni
#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> par, add, val;
    vector<vector<int>> grp;

    dsu(int n) : par(n, -1), add(n, 0), val(n, 0) {
        grp.resize(n);
        for (int i = 0; i < n; i++) {
            grp[i].push_back(i);
        }
    }

    int trace(int u) { return par[u] < 0 ? u : trace(par[u]); }

    bool connect(int u, int v) {
        if ((u = trace(u)) == (v = trace(v))) {
            return false;
        }
        if (par[u] > par[v]) {
            swap(par[u], par[v]);
        }
        for (int vs : grp[v]) {
            grp[u].push_back(vs);
            val[vs] += add[v] - add[u];
        }
        par[u] += par[v];
        grp[v].clear(); add[v] = 0; par[v] = u;
        return true;
    }
    
    int size(int u) { return -par[trace(u)]; }

    int value(int u) {
        return val[u] + add[trace(u)];
    }

    void add_subtree(int u, int v) {
        add[trace(u)] += v;
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<pair<int, int>>> eq(n);
    vector<int> a(n);
    for (int u = 0; u < n; u++) {
        int ov = -1;
        for (int v : adj[u]) {
            if (ov != -1) {
                // x[ov] + a[ov] = x[v] + a[v]
                // x[v] = x[]
                eq[ov].push_back({v, a[ov] - a[v]});
                eq[v].push_back({ov, a[v] - a[ov]});
            }
            ov = v;
        }
        for (int v : adj[u]) {
            a[u]++; a[v]--;
        }
    }
    vector<int> ans(n), vis(n);
    auto DFS = [&](this const auto& DFS, int u, int val) -> void {
        ans[u] = val;
        vis[u] = true;
        for (auto [v, w] : eq[u]) {
            if (!vis[v]) {
                DFS(v, val + w);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            DFS(i, 0);
        }
    }
    int mi = *min_element(ans.begin(), ans.end());
    for (int v : ans) {
        cout << v + (n - mi) << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; // cin >> t;
    while (t--) {
        solve();
    }
}