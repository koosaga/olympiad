#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using llf = long double;
const int MAXN = 505;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	vector<pi> a[2];
	for (int i = 0; i < 2; i++) {
		int n, m;
		cin >> n >> m;
		for (int j = 0; j < n; j++) {
			string s;
			cin >> s;
			for (int k = 0; k < m; k++) {
				if (s[k] == 'o')
					a[i].push_back({j, k});
			}
		}
	}
	auto print = [&](pi p) { cout << p[1] << " " << p[0] << "\n"; };
	if (sz(a[0]) == 1) {
		print(a[0][0]);
		print(a[0][0]);
		return 0;
	}
	if (sz(a[0]) == 2) {
		print(a[0][0]);
		int dx = a[1][1][0] - a[1][0][0];
		int dy = a[1][1][1] - a[1][0][1];
		print({a[0][1][0] - dx, a[0][1][1] - dy});
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		for (auto &[x, y] : a[1]) {
			tie(x, y) = make_pair(y, -x);
		}
		sort(all(a[1]));
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int dx = a[1][j][0] - a[0][i][0];
				int dy = a[1][j][1] - a[0][i][1];
				for (auto &p : a[1])
					p[0] -= dx, p[1] -= dy;
				vector<pi> srces;
				for (auto &p : a[0]) {
					if (!binary_search(all(a[1]), p)) {
						srces.push_back(p);
					}
				}
				if (sz(srces) == 0) {
					print(a[0][0]);
					print(a[0][0]);
					return 0;
				}
				if (sz(srces) == 1) {
					print(srces[0]);
					for (auto &p : a[1]) {
						if (!binary_search(all(a[0]), p)) {
							print(p);
						}
					}
					return 0;
				}
				for (auto &p : a[1])
					p[0] += dx, p[1] += dy;
			}
		}
	}
}