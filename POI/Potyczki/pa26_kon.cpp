#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k, n;
	cin >> k >> n;
	vector<int> dp(n, 1);
	vector<pi> segs;
	for (int i = 2; i <= k; i++) {
		int m;
		cin >> m;
		vector<int> vis(n, 0);
		vector<int> nxt(m, i);
		for (int j = 0; j < m; j++) {
			int q;
			cin >> q;
			q--;
			if (q == -1)
				continue;
			else {
				nxt[j] = dp[q];
				vis[q] = 1;
			}
		}
		for (int j = 0; j < n; j++) {
			if (!vis[j])
				segs.push_back({dp[j], i - 1});
		}
		n = m;
		dp = nxt;
	}
	for (int j = 0; j < n; j++) {
		segs.push_back({dp[j], k});
	}
	vector<int> dx(k + 1);
	for (auto &[l, r] : segs) {
		dx[l - 1]++;
		dx[r]--;
	}
	for (int i = 1; i <= k; i++)
		dx[i] += dx[i - 1];
	cout << *max_element(all(dx)) << "\n";
}