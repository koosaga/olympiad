#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

vector<vector<pi>> gph;
vector<lint> a;
vector<lint> cost;

int dfs(int x, int p, lint c) {
    vector<int> v;
    for (auto &[w, y] : gph[x]) {
        if (y != p)
            v.push_back(dfs(y, x, c) + w);
    }
    sort(all(v));
    if (sz(v) == 0)
        return 0;
    for (int i = 0; i < sz(v) - 1; i++)
        cost.push_back(v[i] * c);
    return v.back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    cr(gph, n);
    cr(a, n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        gph[u].push_back({w, v});
        gph[v].push_back({w, u});
    }
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++) {
        cost.push_back(a[i] * dfs(i, -1, a[i]));
    }
    sort(all(cost));
    reverse(all(cost));
    if (m < sz(cost))
        cost.resize(m);
    cout << accumulate(all(cost), 0ll) << "\n";
}