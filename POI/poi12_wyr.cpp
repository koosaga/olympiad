#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
lint gcd(lint x, lint y) { return y ? gcd(y, x % y) : x; }
lint mod(lint a, lint b) { return ((a % b) + b) % b; }

// returns g = gcd(a, b); finds x, y such that g = ax + by
lint ext_gcd(lint a, lint b, lint &x, lint &y) {
	lint xx = y = 0;
	lint yy = x = 1;
	while (b) {
		lint q = a / b;
		lint t = b;
		b = a % b;
		a = t;
		t = xx;
		xx = x - q * xx;
		x = t;
		t = yy;
		yy = y - q * yy;
		y = t;
	}
	return a;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
lint mod_inverse(lint a, lint n) {
	lint x, y;
	lint g = ext_gcd(a, n, x, y);
	if (g > 1)
		return -1;
	return mod(x, n);
}

// Chinese remainder theorem: find z such that
// z % m1 = r1, z % m2 = r2.  Here, z is unique modulo M = lcm(m1, m2).
// Return (z, M).  On failure, M = -1.
pair<lint, lint> CRT(lint m1, lint r1, lint m2, lint r2) {
	lint s, t;
	lint g = ext_gcd(m1, m2, s, t);
	if (r1 % g != r2 % g)
		return make_pair(0, -1);
	s = mod(s * r2, m2);
	t = mod(t * r1, m1);
	return make_pair(mod(s * (m1 / g) + t * (m2 / g), m1 * (m2 / g)), m1 * (m2 / g));
}

bool cmp(pi a, pi b) { return abs(a[0]) + abs(a[1]) < abs(b[0]) + abs(b[1]); }

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, x, y;
	cin >> n >> x >> y;
	int g = gcd(x, y);
	x /= g;
	y /= g;
	if (x > y)
		swap(x, y);
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
		if (x % g) {
			cout << "-1\n";
			return 0;
		}
		x /= g;
	}
	int ix = mod_inverse(x, y);		// x t = 1 mod y
	int iy = mod_inverse(y % x, x); // y t = 1 mod x
	a.insert(a.begin(), 0);
	a.insert(a.end(), 0);
	pi p{0, 0};
	lint dap = 0;
	auto cost = [&](pi a) { return abs(a[0]) + abs(a[1]); };
	auto shift = [&](pi a, lint d) { return pi{a[0] + d * y, a[1] - d * x}; };
	vector<pi> xinc, yinc;
	for (int i = 1; i < sz(a); i++) {
		int val = abs(a[i] - a[i - 1]);
		lint amin = mod(1ll * val * ix, y);
		pi ans{lint(1e18), lint(1e18)};
		vector<pi> jeong, yeok;
		for (lint j = -2; j <= 2; j++) {
			pi q = {amin + j * y, (val - amin * x) / y - j * x};
			ans = min(ans, q, cmp);
		}
		yeok.push_back({cost(shift(ans, -1)) - cost(ans), 1});
		yeok.push_back({cost(shift(ans, -2)) - cost(shift(ans, -1)), lint(1e18)});
		jeong.push_back({cost(shift(ans, +1)) - cost(ans), 1});
		auto sh = shift(ans, +1);
		if (sh[1] >= x) {
			lint d = sh[1] / x;
			jeong.push_back({cost(shift(ans, 2)) - cost(shift(ans, 1)), d});
			jeong.push_back({cost(shift(ans, d + 2)) - cost(shift(ans, d + 1)), 1});
			jeong.push_back({cost(shift(ans, d + 3)) - cost(shift(ans, d + 2)), lint(1e18)});
		}
		dap += cost(ans);
		if (a[i] - a[i - 1] < 0) {
			p[0] -= ans[0];
			p[1] -= ans[1];
			for (auto &x : jeong)
				yinc.push_back(x);
			for (auto &x : yeok)
				xinc.push_back(x);

		} else {
			p[0] += ans[0];
			p[1] += ans[1];
			for (auto &x : jeong)
				xinc.push_back(x);
			for (auto &x : yeok)
				yinc.push_back(x);
		}
	}
	sort(all(xinc));
	sort(all(yinc));
	auto consume = [&](vector<pi> &v, lint k) {
		for (auto &[a, b] : v) {
			lint d = min(b, k);
			dap += d * a;
			k -= d;
		}
		return dap;
	};
	if (p[0] < 0)
		consume(xinc, -p[0] / y);
	if (p[1] < 0)
		consume(yinc, -p[1] / x);
	cout << dap / 2 << "\n";
}