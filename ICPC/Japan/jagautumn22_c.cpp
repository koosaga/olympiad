#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 420;

lint dp[MAXN][MAXN], adj[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<pi>> gph(n * m);
    lint z = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            z += x;
            int u = i * m + j, v = (i + 1) * m + j;
            gph[u].push_back({x, v});
            gph[v].push_back({x, u});
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            int x;
            cin >> x;
            z += x;
            int u = i * m + j, v = i * m + j + 1;
            gph[u].push_back({x, v});
            gph[v].push_back({x, u});
        }
    }
    auto get = [&](int i, int j) { return i * m + j; };
    vector<int> cyc_order;
    for (int i = 1; i < m - 1; i++) {
        cyc_order.push_back(get(0, i));
    }
    for (int i = 1; i < n - 1; i++) {
        cyc_order.push_back(get(i, m - 1));
    }
    for (int i = m - 2; i >= 1; i--) {
        cyc_order.push_back(get(n - 1, i));
    }
    for (int i = n - 2; i >= 1; i--) {
        cyc_order.push_back(get(i, 0));
    }
    for (int i = 0; i < sz(cyc_order); i++) {
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        vector<lint> dist(n * m, 1e18);
        auto enq = [&](int x, lint v) {
            if (dist[x] > v) {
                dist[x] = v;
                pq.push({v, x});
            }
        };
        enq(cyc_order[i], 0);
        while (sz(pq)) {
            auto x = pq.top();
            pq.pop();
            if (dist[x[1]] != x[0])
                continue;
            for (auto &[w, y] : gph[x[1]]) {
                enq(y, w + x[0]);
            }
        }
        for (int j = 0; j < sz(cyc_order); j++) {
            adj[i][j] = dist[cyc_order[j]];
        }
    }
    n = sz(cyc_order);
    if (n == 0) {
        cout << z << "\n";
        return 0;
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n; i++)
        dp[i][i] = 0;
    {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 2; j <= n; j += 2) {
                for (int k = i + 1; k < j; k += 2) {
                    dp[i][j] = min(dp[i][j], dp[i + 1][k] + adj[i][k] + dp[k + 1][j]);
                }
            }
        }
    }
    cout << z + dp[0][n] << "\n";
}