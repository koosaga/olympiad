#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k, m;
    cin >> n >> k >> m;
    vector<lint> dp(m, 1e18);
    vector<vector<pi>> bucks(k);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int k, m, c;
        cin >> k >> m >> c;
        bucks[k - 1].push_back({m, c});
    }
    for (int i = 0; i < k; i++) {
        vector<lint> nxt(m, 1e18);
        for (auto &[q, c] : bucks[i]) {
            for (int j = 0; j < m; j++) {
                nxt[(j + q) % m] = min(nxt[(j + q) % m], dp[j] + c);
            }
        }
        dp = nxt;
    }
    vector<lint> dist(m, 1e18);
    dist[0] = 0;
    vector<int> vis(m);
    for (int i = 0; i < m; i++) {
        lint curd = 1e17;
        int pos = -1;
        for (int j = 0; j < m; j++) {
            if (!vis[j] && curd > dist[j]) {
                curd = dist[j];
                pos = j;
            }
        }
        if (pos == -1)
            break;
        vis[pos] = 1;
        for (int j = 0; j < m; j++) {
            dist[(pos + j) % m] = min(dist[(pos + j) % m], dist[pos] + dp[j]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (!vis[i])
            cout << "-1\n";
        else
            cout << dist[i] << "\n";
    }
}