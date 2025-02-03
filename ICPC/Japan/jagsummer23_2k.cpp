#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 250005;
const int MAXT = 530000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m;
    vector<vector<pi>> gph(n), rev(n);
    map<pi, int> mp;
    vector<lint> dp(m, 1e18);
    vector<int> weights;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        mp[pi{u, v}] = i;
        gph[u].push_back({i, v});
        rev[v].push_back({i, u});
        if (u == 0)
            dp[i] = w;
        weights.push_back(w);
    }
    vector<set<int>> ban(m);
    cin >> k;
    for (int i = 0; i < k; i++) {
        int c = 3;
        vector<int> v(c);
        for (int j = 0; j < c; j++) {
            cin >> v[j];
            v[j]--;
        }
        int x = (mp.count({v[0], v[1]}) ? mp[{v[0], v[1]}] : -1);
        int y = (mp.count({v[1], v[2]}) ? mp[{v[1], v[2]}] : -1);
        if (x >= 0 && y >= 0) {
            ban[y].insert(x);
        }
    }
    for (int i = 1; i < n; i++) {
        sort(all(rev[i]), [&](const pi &a, const pi &b) { return dp[a[0]] < dp[b[0]]; });
        for (auto &[e2, j] : gph[i]) {
            for (auto &[e1, k] : rev[i]) {
                if (!ban[e2].count(e1)) {
                    dp[e2] = dp[e1] + weights[e2];
                    break;
                }
            }
        }
    }
    lint ans = 1e18;
    for (auto &[i, _] : rev[n - 1])
        ans = min(ans, dp[i]);
    if (ans > 1e17)
        ans = -1;
    cout << ans << "\n";
}