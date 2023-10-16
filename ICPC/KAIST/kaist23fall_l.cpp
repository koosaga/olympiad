#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

bool cmp(pi a, pi b) {
	long double approx = 1.0L * a[1] * b[0] - 1.0L * a[0] * b[1];
	if (fabs(approx) > 1e18)
		return approx > 0;
	return a[1] * b[0] - a[0] * b[1] > 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, s, r;
	cin >> n >> s >> r;
	vector<int> cost(305);
	for (int i = 0; i < n; i++) {
		int c, p;
		cin >> c >> p;
		cost[c] = max(cost[c], p);
	}
	int j = 1;
	for (int i = 1; i <= 300; i++) {
		if (cmp(pi{cost[j], j}, pi{cost[i], i}))
			j = i;
	}
	vector<int> dp(100005);
	for (int i = 0; i < sz(dp); i++) {
		for (int j = 1; j <= 300 && i + j < sz(dp); j++) {
			dp[i + j] = max(dp[i + j], dp[i] + cost[j]);
		}
	}
	pi ans{1, 0};
	for (int i = 0; i < sz(dp); i++) {
		if (dp[i] == 0)
			continue;
		auto get_frac = [&](int p) {
			lint used = i + 1ll * p * j;
			lint gained = dp[i] + 1ll * p * cost[j];
			return pi{used * gained + 1ll * r * s, gained};
		};
		int s = 0, e = 1e6;

		while (s != e) {
			int m = (s + e) / 2;
			if (cmp(get_frac(m), get_frac(m + 1)))
				e = m;
			else
				s = m + 1;
		}
		if (cmp(get_frac(s), ans))
			ans = get_frac(s);
	}
	lint g = gcd(ans[0], ans[1]);
	ans[0] /= g;
	ans[1] /= g;
	cout << ans[0] << " " << ans[1] << endl;
}