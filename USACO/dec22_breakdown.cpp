#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 310;
pi times[MAXN][MAXN][MAXN];
int L[MAXN * MAXN], R[MAXN * MAXN], ans[MAXN * MAXN];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n, k;
	cin >> n >> k;
	vector<vector<pi>> a(n + 8 - k, vector<pi>(n + 8 - k, pi{0, n * n}));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j][0];
		}
	}
	for (int i = 0; i < n * n; i++) {
		int u, v;
		cin >> u >> v;
		a[u - 1][v - 1][1] = i;
	}
	for (int i = 0; i < n + 8 - k; i++) {
		for (int j = 0; j < n + 8 - k; j++) {
			if (max(i, j) >= n) {
				a[i][j][0] = 1e9;
				if (j - i == 1)
					a[i][j][0] = 0;
			}
		}
	}
	int toP = n * n;
	n += 8 - k;
	vector<vector<int>> fuckingL(n, vector<int>(n)), fuckingR(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		iota(all(fuckingL[i]), 0);
		sort(all(fuckingL[i]), [&](int p, int q) { return a[i][p][1] < a[i][q][1]; });
		iota(all(fuckingR[i]), 0);
		sort(all(fuckingR[i]), [&](int p, int q) { return a[p][i][1] < a[q][i][1]; });
	}
	vector<int> vis(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int p1 = 0, p2 = 0, k = 0;
			while (p1 < n && p2 < n) {
				if (vis[fuckingL[i][p1]])
					p1++;
				else if (vis[fuckingR[j][p2]])
					p2++;
				else {
					int k1 = fuckingL[i][p1], k2 = fuckingR[j][p2];
					if (a[i][k1][1] <= a[k2][j][1]) {
						times[i][j][k] = {min(a[i][k1][1], a[k1][j][1]), min(int(1e9), a[i][k1][0] + a[k1][j][0])};
						vis[k1] = 1;
						p1++;
					} else {
						times[i][j][k] = {min(a[i][k2][1], a[k2][j][1]), min(int(1e9), a[i][k2][0] + a[k2][j][0])};
						vis[k2] = 1;
						p2++;
					}
					k++;
				}
			}
			assert(k == n);
			times[i][j][n] = pi{toP, int(1e9)};
			for (int k = n - 1; k >= 0; k--) {
				times[i][j][k][1] = min(times[i][j][k][1], times[i][j][k + 1][1]);
			}
			fill(all(vis), 0);
		}
	}
	memset(ans, 0x3f, sizeof(ans));
	for (int i = 0; i < n; i++) {
		memset(L, 0x3f, sizeof(L));
		memset(R, 0x3f, sizeof(R));
		for (int j = 0; j < n; j++) {
			int p1 = 0, p2 = 0;
			while (p1 <= n && p2 <= n) {
				int t = min(times[0][j][p1][0], times[j][i][p2][0]);
				int w = times[0][j][p1][1] + times[j][i][p2][1];
				L[t] = min(L[t], w);
				if (times[0][j][p1][0] < times[j][i][p2][0])
					p1++;
				else
					p2++;
			}
		}
		for (int j = 0; j < n; j++) {
			int p1 = 0, p2 = 0;
			while (p1 <= n && p2 <= n) {
				int t = min(times[i][j][p1][0], times[j][n - 1][p2][0]);
				int w = times[i][j][p1][1] + times[j][n - 1][p2][1];
				R[t] = min(R[t], w);
				if (times[i][j][p1][0] < times[j][n - 1][p2][0])
					p1++;
				else
					p2++;
			}
		}
		for (int j = n * n; j >= 0; j--) {
			L[j] = min(L[j], L[j + 1]);
			R[j] = min(R[j], R[j + 1]);
		}
		for (int j = 0; j <= n * n; j++) {
			ans[j] = min(ans[j], L[j] + R[j]);
		}
	}
	for (int i = 1; i <= toP; i++) {
		if (ans[i] > 8.1e8)
			ans[i] = -1;
		cout << ans[i] << "\n";
	}
}