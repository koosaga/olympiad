#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<string> s(n);
	for (auto &z : s)
		cin >> z;
	vector<int> good(n, 1);
	while (count(all(good), 1) > 1) {
		vector<int> subs;
		for (int j = 0; j < n; j++) {
			if (randint(0, 1))
				subs.push_back(j);
		}
		vector<vector<int>> cnt(m, vector<int>(4));
		for (int j = 0; j < sz(subs); j++) {
			for (int k = 0; k < m; k++) {
				cnt[k][s[subs[j]][k] - 'A']++;
			}
		}
		for (int j = 0; j < sz(subs); j++) {
			int tot = (sz(subs) - 1) * (m - k);
			for (int k = 0; k < m; k++) {
				tot -= cnt[k][s[subs[j]][k] - 'A'] - 1;
				if (tot < 0)
					break;
			}
			if (tot != 0)
				good[subs[j]] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		if (good[i]) {
			cout << i + 1 << "\n";
		}
	}
}