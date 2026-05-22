#include <bits/stdc++.h>
using namespace std;

using lint = long long;
using pi = array<int, 2>;

#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

lint can_mul(lint x, lint y) {
	return x <= 3e18 / y && (x * y <= lint(1e18));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	vector<pair<lint, pi>> mp;

	for (int i = 1; i <= 2000000; i++) {
		lint cur = i;
		for (int j = i + 1;; j++) {
			lint g = j / gcd(cur, (lint)j);
			if (!can_mul(cur, g))
				break;
			cur *= g;
			mp.push_back({cur, pi{i, j}});
		}
	}

	sort(all(mp), [](const pair<lint, pi>& a, const pair<lint, pi>& b) {
		if (a.first != b.first) return a.first < b.first;
		return a.second < b.second; // minimum pair for duplicate first
	});

	mp.erase(unique(all(mp), [](const pair<lint, pi>& a, const pair<lint, pi>& b) {
		return a.first == b.first;
	}), mp.end());

	int q;
	cin >> q;

	while (q--) {
		lint z;
		cin >> z;

		auto it = lower_bound(all(mp), z, [](const pair<lint, pi>& a, lint val) {
			return a.first < val;
		});

		if (it != mp.end() && it->first == z) {
			cout << it->second[0] << " " << it->second[1] << "\n";
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