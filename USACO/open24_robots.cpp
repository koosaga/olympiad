#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

lint divs(lint a, lint b) {
	if (b == 0)
		return 1e18;
	return (a + b - 1) / b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint l, r, n, k;
	cin >> l >> r >> n >> k;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	vector<lint> dist(r);
	for (int i = 1; i < r; i++) {
		dist[i] = min(divs((l / r) * i * k, k - 1), divs((l / r) * (r - i) * k, k + 1));
	}
	auto f = [&](lint t, int v) {
		lint pos = (divs(t, k) + (l / r) * (v + 1)) % l;
		auto it = lower_bound(all(a), pos);
		lint dist = (it == a.end() ? (l + a[0]) : *it) - pos;
		return k * (dist + divs(t, k));
	};
	vector<vector<lint>> dp(1 << (r - 1), vector<lint>(r - 1, 1e18));
	for (int i = 0; i < r - 1; i++) {
		dp[1 << i][i] = f(dist[i + 1], i);
	}
	for (int i = 1; i < sz(dp); i++) {
		for (int j = 0; j < r - 1; j++) {
			if ((i >> j) % 2 == 0)
				continue;
			dp[i][j] = f(dp[i][j], j);
			for (int k = 0; k < r - 1; k++) {
				if ((i >> k) % 2 == 1)
					continue;
				dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + dist[(k - j + r) % r]);
			}
		}
	}
	cout << *min_element(all(dp.back())) << "\n";
}