#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	auto f = [&](int l, int r) {
		lint sx = 1e9, ex = -1e9, sy = 1e9, ey = -1e9;
		for (int i = l; i < r; i++) {
			sx = min(sx, a[i][0]);
			ex = max(ex, a[i][0]);
			sy = min(sy, a[i][1]);
			ey = max(ey, a[i][1]);
		}
		lint ans = 0;
		for (int i = l; i < r; i++) {
			ans = max(ans, min({a[i][0] - sx, ex - a[i][0], a[i][1] - sy, ey - a[i][1]}));
		}
		return ans;
	};
	auto solve = [&]() {
		sort(all(a));
		int s = 0, e = n;
		while (s != e) {
			int m = (s + e) / 2;
			if (f(0, m) < f(m, n))
				s = m + 1;
			else
				e = m;
		}
		lint ans = 1e18;
		for (int i = -2; i <= 2; i++) {
			if (s + i < 0 || s + i > n)
				continue;
			ans = min(ans, max(f(0, s + i), f(s + i, n)));
		}
		return ans;
	};
	auto ok = [&](int w) {
		lint sx = 1e9, ex = -1e9, sy = 1e9, ey = -1e9;
		for (int i = 0; i < n; i++) {
			sx = min(sx, a[i][0]);
			ex = max(ex, a[i][0]);
			sy = min(sy, a[i][1]);
			ey = max(ey, a[i][1]);
		}
		lint ans = 0;
		vector<int> foo;
		for (int i = 0; i < n; i++) {
			lint k = min({a[i][0] - sx, ex - a[i][0], a[i][1] - sy, ey - a[i][1]});
			if (k <= w)
				continue;
			foo.push_back(i);
		}
		{
			lint sx = 1e9, ex = -1e9, sy = 1e9, ey = -1e9;
			for (auto &i : foo) {
				sx = min(sx, a[i][0]);
				ex = max(ex, a[i][0]);
				sy = min(sy, a[i][1]);
				ey = max(ey, a[i][1]);
			}
			lint ans = 0;
			for (auto &i : foo) {
				ans = max(ans, min({a[i][0] - sx, ex - a[i][0], a[i][1] - sy, ey - a[i][1]}));
			}
			return ans <= w;
		}
	};
	auto idk = [&]() {
		int s = 0, e = 1e9;
		while (s != e) {
			int m = (s + e) / 2;
			if (ok(m))
				e = m;
			else
				s = m + 1;
		}
		return s;
	};
	lint ans = idk();
	for (int i = 0; i < 2; i++) {
		ans = min(ans, solve());
		for (int j = 0; j < n; j++)
			swap(a[j][0], a[j][1]);
	}
	cout << ans << "\n";
}