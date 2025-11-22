#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

pi operator+(const pi &a, const pi &b) { return pi{a[0] + b[0], a[1] + b[1]}; }
pi operator-(const pi &a, const pi &b) { return pi{a[0] - b[0], a[1] - b[1]}; }
lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }
lint ccw(pi a, pi b, pi c) { return ccw(b - a, c - a); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	vector<pi> ch;
	for (int i = 0; i < n; i++) {
		while (sz(ch) >= 2 && ccw(ch[sz(ch) - 2], ch.back(), a[i]) <= 0)
			ch.pop_back();
		ch.push_back(a[i]);
	}
	cin >> q;
	while (q--) {
		int x;
		cin >> x;
		int p = lower_bound(all(ch), pi{x, -1}) - ch.begin();
		auto [x1, y1] = ch[p - 1];
		auto [x2, y2] = ch[p];
		lint U = y1 * (x2 - x1) + (x - x1) * (y2 - y1);
		lint D = x2 - x1;
		lint g = gcd(U, D);
		cout << U / g << " " << D / g << "\n";
	}
}