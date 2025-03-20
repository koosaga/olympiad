#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using llf = long double;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int DEV = 1557;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<llf> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	reverse(all(a));
	vector<llf> dp(DEV * 2 + 1);
	dp[DEV] = 1;
	llf ans = 0;
	llf mean = 0;
	for (int i = 0; i < n; i++) {
		int old_mean = (int)round(mean);
		mean += a[i];
		int new_mean = (int)round(mean);
		vector<llf> nxt(DEV * 2 + 1);
		for (int j = 0; j < sz(dp); j++) {
			int value = j + old_mean - new_mean;
			if (value + 1 >= 0 && value + 1 < sz(nxt))
				nxt[value + 1] += dp[j] * a[i];
			if (value >= 0 && value < sz(nxt))
				nxt[value] += dp[j] * (1 - a[i]);
		}
		dp = nxt;
		llf cur = 0;
		for (int j = 0; j < sz(dp); j++) {
			if (2 * (j + new_mean - DEV) - (i + 1) >= k)
				cur += dp[j];
		}
		ans = max(ans, cur);
	}
	cout << fixed << setprecision(20) << ans << "\n";
}