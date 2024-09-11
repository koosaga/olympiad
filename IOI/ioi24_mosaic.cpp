#include <bits/stdc++.h>
#include <vector>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

int d0[3][MAXN], d1[3][MAXN];
lint ps0[3][MAXN], ps1[3][MAXN];
lint psi0[3][MAXN], psi1[3][MAXN];

vector<long long> mosaic(vector<int> X, vector<int> Y, vector<int> T, vector<int> B, vector<int> L, vector<int> R) {
	while (sz(X) < 3)
		X.push_back(0);
	while (sz(Y) < 3)
		Y.push_back(0);
	for (int i = 0; i < sz(X); i++)
		d0[0][i] = X[i];
	for (int i = 0; i < sz(Y); i++)
		d1[0][i] = Y[i];
	for (int i = 1; i < 3; i++) {
		d0[i][0] = Y[i];
		d1[i][0] = X[i];
		for (int j = 1; j < sz(X); j++) {
			d0[i][j] = (1 - d0[i - 1][j]) && (1 - d0[i][j - 1]);
		}
		for (int j = 1; j < sz(Y); j++) {
			d1[i][j] = (1 - d1[i - 1][j]) && (1 - d1[i][j - 1]);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < MAXN; j++) {
			ps0[i][j] = (j ? ps0[i][j - 1] : 0) + d0[i][j];
			ps1[i][j] = (j ? ps1[i][j - 1] : 0) + d1[i][j];
			psi0[i][j] = (j ? psi0[i][j - 1] : 0) + d0[i][j] * j;
			psi1[i][j] = (j ? psi1[i][j - 1] : 0) + d1[i][j] * j;
		}
	}
	vector<lint> ans(sz(T));
	auto f = [&](int x, int y) {
		int d = min(x, y) - 2;
		if (d >= 0) {
			x -= d;
			y -= d;
		}
		if (x <= 2)
			return d0[x][y];
		return d1[y][x];
	};
	auto h = [&](int *d0, int *d1, lint *s0, lint *s1, lint *si0, lint *si1, int x, int y) {
		lint ans = 0;
		ans -= (si1[x - 1] - si1[x - y + 2]);
		ans -= (si0[y - 1] - si0[1]);
		ans += 1ll * (y - 2) * (s1[x - y + 2] - s1[2]);
		ans += 1ll * y * (s0[y - 1] - s0[1]);
		ans += 1ll * x * (s1[x - 1] - s1[x - y + 2]);
		return ans;
	};
	auto g = [&](int x, int y) {
		if (x < 0 || y < 0)
			return 0ll;
		lint ans = 0;
		if (x <= 2) {
			for (int i = 0; i <= x; i++)
				ans += ps0[i][y];
			return ans;
		}
		if (y <= 2) {
			for (int i = 0; i <= y; i++)
				ans += ps1[i][x];
			return ans;
		}
		for (int i = 0; i <= 2; i++)
			ans += ps0[i][y];
		for (int i = 0; i <= 2; i++)
			ans += ps1[i][x] - ps1[i][2];
		if (x >= y) {
			ans += h(d0[2], d1[2], ps0[2], ps1[2], psi0[2], psi1[2], x, y);
		} else {
			ans += h(d1[2], d0[2], ps1[2], ps0[2], psi1[2], psi0[2], y, x);
		}
		return ans;
	};
	for (int i = 0; i < sz(T); i++) {
		ans[i] += g(B[i], R[i]) - g(B[i], L[i] - 1) - g(T[i] - 1, R[i]) + g(T[i] - 1, L[i] - 1);
	}
	return ans;
}