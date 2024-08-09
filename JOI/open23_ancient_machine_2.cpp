#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int tab[5005][5005];
int chk[5005][5005];

int solve(int n, int m, int d) {
	int ans = 1e9;
	vector<int> h(m + 1);
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < m; k++) {
			if (tab[i][k])
				h[k] = 0;
			else
				h[k]++;
		}
		vector<int> stk;
		for (int k = 0; k <= m; k++) {
			while (sz(stk) && h[stk.back()] >= h[k]) {
				int y = h[stk.back()];
				stk.pop_back();
				int r = k;
				int l = (sz(stk) ? stk.back() : -1);
				ans = min(ans, (d - y) * (d - (r - l - 1)));
			}
			stk.push_back(k);
		}
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, m, d;
	cin >> n >> m >> d;
	vector<int> c1(d), c2(d);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		c1[x] = c2[y] = 1;
	}
	vector<pi> v1, v2;
	int ans = d * d;
	{
		for (int i = 0; i < d; i++) {
			if (c1[i] && !c1[(i + 1) % d]) {
				int j = (i + 1) % d, ptr = 0;
				while (!c1[j]) {
					ptr++;
					j = (j + 1) % d;
				}
				v1.push_back({(i + 1) % d, ptr});
				ans = min(ans, d * (d - ptr));
			}
		}
		for (int i = 0; i < d; i++) {
			if (c2[i] && !c2[(i + 1) % d]) {
				int j = (i + 1) % d, ptr = 0;
				while (!c2[j]) {
					ptr++;
					j = (j + 1) % d;
				}
				v2.push_back({(i + 1) % d, ptr});
				ans = min(ans, d * (d - ptr));
			}
		}
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		if (c1[x] || c2[y])
			continue;
		chk[x][y] = 1;
	}
	for (auto &[x1, xl] : v1) {
		for (auto &[y1, yl] : v2) {
			for (int p = 0; p < xl; p++) {
				for (int q = 0; q < yl; q++) {
					tab[p][q] = chk[(x1 + p) % d][(y1 + q) % d];
				}
			}
			ans = min(ans, solve(xl, yl, d));
		}
	}
	cout << ans << "\n";
}