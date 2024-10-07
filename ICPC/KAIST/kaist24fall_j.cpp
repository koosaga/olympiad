#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

namespace Euclid {
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
	a = mod(a, n);
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
} // namespace Euclid

pi OneStepCloser(pi p) {
	// p[0] * q[1] - q[0] * p[1] = 1
	if (p[0] == 0) {
		assert(abs(p[1]) == 1);
		return pi{-p[1], 0};
	}
	if (p[1] == 0) {
		assert(abs(p[0]) == 1);
		return pi{0, p[0]};
	}
	int y = Euclid::mod_inverse(p[0], abs(p[1]));
	lint x = (p[0] * y - 1) / p[1];
	assert(y * p[0] - x * p[1] == 1);
	assert(abs(x) < 6e8);
	return pi{x, y};
}

lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }
lint dot(pi a, pi b) { return a[0] * b[0] + a[1] * b[1]; }

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<pi> a(n);
		for (auto &[x, y] : a)
			cin >> x >> y;
		{
			auto it = find(all(a), pi{0, 0});
			if (it != a.end())
				a.erase(it);
			n = sz(a);
		}
		sort(all(a), [&](const pi &p, const pi &q) {
			bool m1 = (p > pi{0, 0});
			bool m2 = (q > pi{0, 0});
			if (m1 != m2)
				return m1 > m2;
			return ccw(p, q) > 0;
		});
		auto ansone = [&]() {
			for (int i = 0; i < n; i++) {
				if (dot(a[0], a[i]) < 0)
					return false;
			}
			return true;
		};
		auto collinear = [&]() {
			for (int i = 1; i < n; i++) {
				if (ccw(a[0], a[i]) != 0)
					return false;
			}
			return true;
		};
		if (collinear()) {
			int g = gcd(abs(a[0][0]), abs(a[0][1]));
			a[0][0] /= g;
			a[0][1] /= g;
			if (ansone()) {
				cout << "1\n" << a[0][0] << " " << a[0][1] << "\n";
				continue;
			}
			cout << "2\n" << a[0][0] << " " << a[0][1] << "\n" << -a[0][0] << " " << -a[0][1] << "\n";
			continue;
		}
		bool ok = 0;
		for (int i = 0; i < n; i++) {
			if (ccw(a[i], a[(i + n - 1) % n]) > 0) {
				ok = 1;
				rotate(a.begin(), a.begin() + i, a.end());
				break;
			}
		}
		if (!ok) {
			cout << "3\n1 0\n0 1\n-696969696969696969 -155788848155788848\n";
			continue;
		}
		int g = gcd(abs(a[0][0]), abs(a[0][1]));
		a[0][0] /= g;
		a[0][1] /= g;
		pi L = a[0];
		pi R = OneStepCloser(a[0]);
		cout << "2\n";
		cout << L[0] << " " << L[1] << "\n";
		cout << R[0] - L[0] * lint(1e9) << " " << R[1] - L[1] * lint(1e9) << "\n";
	}
}