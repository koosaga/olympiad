#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 2005;
using word = bitset<MAXN>;
int a[MAXN][MAXN];

word solve(int l, int r) {
	if (r - l == 1) {
		word w = 0;
		w[l] = 1;
		return w;
	}
	if (a[l + 1][r] == a[l][r])
		return solve(l + 1, r);
	if (a[l][r] == a[l][r - 1])
		return solve(l, r - 1);
	vector<pi> cons;
	for (int j = l; j < r;) {
		int k = j + 1;
		while (k < r && a[k - 1][k + 1] == 2)
			k++;
		cons.push_back({j, k});
		j = k;
	}
	vector<int> isMaj(sz(cons));
	isMaj[0] = 1;
	for (int i = 1; i < sz(cons) - 1; i++) {
		if (isMaj[i - 1])
			continue;
		int a0 = cons[i - 2][1] - cons[i - 2][0];
		int a1 = cons[i - 1][1] - cons[i - 1][0];
		int a2 = cons[i][1] - cons[i][0];
		if (a0 + a2 > a1) {
			if (a[cons[i - 2][0]][cons[i][1]] == a0 + a2) {
				isMaj[i] = isMaj[i - 2];
			} else {
				isMaj[i] = 1 - (isMaj[i - 1] || isMaj[i - 2]);
			}
			continue;
		}
		// fun part?
		int m = cons[i][0];
		int M = 0;
		for (int j = 0; j < i; j++) {
			if (isMaj[j]) {
				M += cons[j][1] - cons[j][0];
			}
		}
		assert(M <= a[l][m]);
		if (M == a[l][m]) {
			if (a[l + 1][m] == a[l][m]) {
				if (a[l][m] != a[l][m + 1] && a[l + 1][m] == a[l + 1][m + 1])
					isMaj[i] = 1;
			} else {
				if (a[l][m] != a[l][m + 1])
					isMaj[i] = 1;
			}
		} else {
			int B = a[l][m];
			int A = m - l - B - M;
			if (M <= A) {
				auto ans = solve(m, r);
				for (int j = 0; j < i; j++) {
					if (isMaj[j]) {
						for (int k = cons[j][0]; k < cons[j][1]; k++)
							ans[k] = 1;
					}
				}
				return ans;
			} else {
				// A=0 M=1 B=2, A < M < B
				// opposite maj is A or M (or both), B cannot be tied even.
				// case 1. opposite strict maj is M
				if (a[l][m] != a[l][m + 1]) {
					continue;
				}
				if (a[m][r] != a[m][r - 1]) {
					auto ans = solve(m, r);
					for (int j = 0; j < i; j++) {
						if (isMaj[j]) {
							for (int k = cons[j][0]; k < cons[j][1]; k++)
								ans[k] = 1;
						}
					}
					return ans;
				}
				// case 2. A is one of majority.
				if (m == r - 1 || a[m][r - 1] == a[m + 1][r - 1])
					isMaj[i] = 1;
			}
		}
	}
	isMaj.back() = 1;
	word ans = 0;
	for (int i = 0; i < sz(cons); i++) {
		if (isMaj[i]) {
			for (int k = cons[i][0]; k < cons[i][1]; k++)
				ans[k] = 1;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			cin >> a[i][j];
	auto ans = solve(0, n);
	for (int i = 0; i < n; i++) {
		if (ans[i])
			cout << i + 1 << " ";
	}
}