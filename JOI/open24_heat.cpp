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
	int n, m;
	cin >> n;
	vector<int> a(n);
	vector<vector<int>> intime(n + 1);
	for (auto &x : a)
		cin >> x;
	cin >> m;
	bool is_sorted = 1;
	int last = -1;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		if (last > x)
			is_sorted = 0;
		last = x;
		intime[x].push_back(i + 1);
	}
	if (is_sorted) {
		int ans = 0;
		for (int i = 1; i < n; i++) {
			for (auto &j : intime[i]) {
				if (a[i])
					a[i]--;
				else if (a[i - 1])
					a[i - 1]--;
				else
					ans++;
			}
		}
		cout << ans << "\n";
		return 0;
	}
	vector<vector<int>> dp(sz(intime[0]) + 1, vector<int>(m + 2, -1e9));
	fill(all(dp[0]), 0);
	for (int i = 0; i < n; i++) {
		vector<vector<int>> nxt(sz(intime[i + 1]) + 1, vector<int>(m + 2, -1e9));
		vector<int> sum(m + 2);
		for (auto &x : intime[i + 1])
			sum[x]++;
		for (int i = 1; i <= m + 1; i++)
			sum[i] += sum[i - 1];
		for (int j1 = 0; j1 <= min(a[i], sz(intime[i])); j1++) {
			for (int k1 = 1; k1 <= m + 1; k1++) {
				int j2 = j1 + sum[k1] - a[i];
				if (j2 > sz(intime[i + 1]))
					break;
				if (j2 < 0)
					continue;
				nxt[j2][k1 - 1] = max(nxt[j2][k1 - 1], dp[j1][k1] + sum.back() - sum[k1]);
			}
		}
		for (int j = 0; j <= sz(intime[i + 1]); j++) {
			for (int k = m; k >= 0; k--) {
				if (sum[k] < j)
					break;
				nxt[j][k] = max(nxt[j][k], nxt[j][k + 1]);
			}
		}
		for (int j1 = 0; j1 <= sz(intime[i]); j1++) {
			int z = -1e9;
			for (int k1 = 0; k1 <= m + 1; k1++) {
				if (0 <= j1 + sum[k1] - a[i] && a[i] >= j1) {
					z = max(z, dp[j1][k1] + sum.back());
				}
				int j2 = j1 + sum[k1] - a[i];
				if (j2 > sz(intime[i + 1]))
					break;
				if (0 <= j2) {
					nxt[j2][k1] = max(nxt[j2][k1], z - sum[k1]);
				}
			}
		}
		int x = -1e9, ptr = 0;
		for (int j2 = 0; j2 <= sz(intime[i + 1]); j2++) {
			int j1 = j2 + a[i] - sum[m + 1];
			while (ptr <= j1 && ptr <= sz(intime[i])) {
				x = max(x, dp[ptr++][m + 1]);
			}
			for (int k2 = 0; k2 <= m + 1; k2++) {
				if (j2 <= sum[k2])
					nxt[j2][k2] = max(nxt[j2][k2], x);
			}
		}
		swap(dp, nxt);
	}
	cout << *max_element(all(dp[0])) << "\n";
}
