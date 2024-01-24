#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 5005;

int dp[MAXN][MAXN];
int a[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<int> idx(n);
    iota(all(idx), 0);
    int ret = 1;
    sort(all(idx), [&](int u, int v) { return pi{a[u], -u} < pi{a[v], -v}; });
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = 2;
        }
    }
    for (int i = 1; i < n - 1; i++) {
        int ans = 0;
        for (auto &j : idx) {
            if (j < i) {
                ans = max(ans, dp[j][i]);
            } else if (j > i) {
                dp[i][j] = max(dp[i][j], ans + 1);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ret = max(ret, dp[i][j]);
        }
    }
    cout << ret << "\n";
}