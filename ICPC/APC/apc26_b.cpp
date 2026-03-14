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
	int n;
	cin >> n;
	vector<vector<int>> gph(n);
	vector<int> p(n);
	vector<int> dp(n), dep(n);
	for (int i = 1; i < n; i++)
		cin >> p[i], p[i]--;
	for (int i = 1; i < n; i++)
		gph[p[i]].push_back(i), dep[i] = dep[p[i]] + 1;
	p[0] = -1;
	int s = 0, e = n;
	auto trial = [&](int x) {
		for (int i = n - 1; i >= 0; i--) {
			if (sz(gph[i]) == 0) {
				dp[i] = (i <= x ? 1 : -1);
			} else {
				dp[i] = 0;
				for (auto &j : gph[i]) {
					dp[i] += dp[j];
				}
				dp[i] = clamp(dp[i], -1, 1);
			}
		}
		if (dp[0] >= 0)
			return true;
		return false;
	};
	while (s != e) {
		int m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m + 1;
	}
	cout << s + 1 << "\n";
}