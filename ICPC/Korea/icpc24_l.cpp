#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
pi operator-(const pi &a, const pi &b) { return pi{a[0] - b[0], a[1] - b[1]}; }

pi shoot(pi x, pi d) {
	int g = gcd(abs(d[0]), abs(d[1]));
	return pi{x[0] + d[0] / g, x[1] + d[1] / g};
}

lint ccw(pi a, pi b, pi c) {
	b = b - a;
	c = c - a;
	return b[0] * c[1] - c[0] * b[1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	pi a[3];
	for (int i = 0; i < 3; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	lint retL = 0, retS = 5e18;
	for (int i = 0; i < 8; i++) {
		pi b[3];
		for (int j = 0; j < 3; j++) {
			pi l = a[j], r = a[(j + 1) % 3];
			if ((i >> j) & 1)
				swap(l, r);
			b[j] = shoot(l, r - l);
			if (b[j] == r) {
				cout << "-1\n";
				return 0;
			}
		}
		retL = max(retL, abs(ccw(b[0], b[1], b[2])));
		retS = min(retS, abs(ccw(b[0], b[1], b[2])));
	}
	cout << retL << " " << retS << endl;
}