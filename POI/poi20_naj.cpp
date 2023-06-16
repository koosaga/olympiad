#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

lint can_mul(lint x, lint y) { return x <= 3e18 / y && (x * y <= lint(1e18)); }

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	map<lint, pi> mp;
	for (int i = 1; i <= 2000000; i++) {
		lint cur = i;
		for (int j = i + 1;; j++) {
			lint g = j / gcd(cur, j);
			if (!can_mul(cur, g))
				break;
			cur *= g;
			if (!mp.count(cur)) {
				mp[cur] = pi{i, j};
			}
		}
	}
	int q;
	cin >> q;
	while (q--) {
		lint z;
		cin >> z;
		if (mp.count(z)) {
			cout << mp[z][0] << " " << mp[z][1] << "\n";
			continue;
		}
		lint s = 0, e = 1e9;
		while (s != e) {
			lint m = (s + e + 1) / 2;
			if (m * (m + 1) <= z)
				s = m;
			else
				e = m - 1;
		}
		if (s * (s + 1) == z)
			cout << s << " " << s + 1 << "\n";
		else
			cout << "NIE\n";
	}
}