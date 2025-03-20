#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint n, m, s;
	cin >> n >> m >> s;
	vector<lint> cnd = {1, n, s};
	vector<pi> intv(m);
	for (auto &[l, r] : intv) {
		cin >> l >> r;
		if (l > 1)
			cnd.push_back(l - 1);
		if (r < n)
			cnd.push_back(r + 1);
	}
	pi ans{lint(1e18), -1};
	for (auto &x : cnd) {
		bool ok = 1;
		for (auto &[l, r] : intv) {
			if (l <= x && x <= r)
				ok = 0;
		}
		if (ok) {
			ans = min(ans, pi{abs(s - x), x});
		}
	}
	cout << ans[1] << "\n";
}