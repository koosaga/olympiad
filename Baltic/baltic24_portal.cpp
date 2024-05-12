#include <bits/stdc++.h>
using namespace std;
using lint = __int128;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
#define abs fuck

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

lint abs(lint x) { return x > 0 ? x : -x; }

pair<lint, lint> solve(lint a, lint b) {
	lint x, y;
	Euclid::ext_gcd(a, b, x, y);
	return make_pair(x, y);
}
pair<pi, pi> normalize(pi a, pi b) {
	if (a[1] == 0)
		return {a, b};
	if (b[1] == 0)
		return {b, a};
	lint g = gcd(abs(a[1]), abs(b[1]));
	lint k = a[1] / g, l = b[1] / g;
	lint c = l * a[0] - k * b[0];
	auto [p, q] = solve(k, l);
	auto d = pi{p * a[0] + q * b[0], p * a[1] + q * b[1]};
	return make_pair(pi{abs(c), 0}, d);
}

vector<pi> comp(vector<pi> a) {
	int n = sz(a);
	{
		auto [z, w] = normalize(a[0], a[1]);
		a[0] = z;
		a[1] = w;
	}
	for (int i = 2; i < n; i++) {
		auto [z, w] = normalize(a[1], a[i]);
		a[0][0] = gcd(a[0][0], z[0]);
		a[1] = w;
	}
	a.resize(2);
	return a;
}

lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }

/*
 * http://stackoverflow.com/a/25115163
 */
std::ostream &operator<<(std::ostream &os, const __int128 i) noexcept {
	std::ostream::sentry s(os);
	if (s) {
		unsigned __int128 tmp = i < 0 ? -i : i;
		char buffer[128];
		char *d = std::end(buffer);
		do {
			--d;
			*d = "0123456789"[tmp % 10];
			tmp /= 10;
		} while (tmp != 0);
		if (i < 0) {
			--d;
			*d = '-';
		}
		int len = std::end(buffer) - d;
		if (os.rdbuf()->sputn(d, len) != len) {
			os.setstate(std::ios_base::badbit);
		}
	}
	return os;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (auto &[x, y] : a) {
		int px, py;
		cin >> px >> py;
		x = px;
		y = py;
	}
	if (n <= 2) {
		cout << "-1\n";
		return 0;
	}
	for (int i = 1; i < n; i++)
		a[i][0] -= a[0][0], a[i][1] -= a[0][1];
	a.erase(a.begin());
	n = sz(a);
	for (int i = 0; i < n; i++) {
		if (a[i] < pi{0, 0})
			a[i][0] *= -1, a[i][1] *= -1;
	}
	if (count(all(a), pi{0, 0})) {
		a.erase(find(all(a), pi{0, 0}));
	}
	sort(all(a), [&](const pi &p, const pi &q) { return ccw(p, q) > 0; });
	vector<pi> b;
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && ccw(a[i], a[j]) == 0)
			j++;
		int g = gcd(abs(a[i][0]), abs(a[i][1]));
		a[i][0] /= g;
		a[i][1] /= g;
		for (int k = i + 1; k < j; k++) {
			int g2 = gcd(abs(a[k][0]), abs(a[k][1]));
			g = gcd(g, g2);
		}
		a[i][0] *= g;
		a[i][1] *= g;
		b.push_back(a[i]);
		i = j;
	}
	if (sz(b) == 1) {
		cout << "-1\n";
		return 0;
	}
	b = comp(b);
	cout << abs(ccw(b[0], b[1])) << "\n";
}