#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int q, n;
		cin >> q >> n;
		vector<int> ord(n);
		vector<vector<vector<int>>> tocons(n);
		while (q--) {
			int p, k;
			cin >> p >> k;
			p--;
			vector<int> ords(k);
			for (auto &x : ords) {
				cin >> x;
				x--;
				ord[x] = max(ord[x], p);
			}
			tocons[p].push_back(ords);
		}
		vector<vector<int>> pos(n);
		set<int> s;
		for (int i = 0; i < n; i++) {
			pos[ord[i]].push_back(i);
		}
		bool bad = 0;
		for (int i = 0; i < n; i++) {
			for (auto &j : pos[i])
				s.insert(j);
			if (sz(tocons[i]) == 0) {
				if (sz(s) == 0) {
					bad = 1;
					break;
				}
				s.erase(s.begin());
				continue;
			}
			map<int, int> mp;
			for (auto &v : tocons[i]) {
				for (auto &w : v)
					mp[w]++;
			}
			bool ok = 0;
			for (auto &[k, v] : mp) {
				if (v == sz(tocons[i]) && s.count(k)) {
					s.erase(k);
					ok = 1;
					break;
				}
			}
			if (!ok) {
				bad = 1;
				break;
			}
		}
		cout << (!bad ? "yes" : "no") << "\n";
	}
}