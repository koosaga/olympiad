#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 888;

lint a[MAXN][MAXN], D[MAXN][MAXN], E[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			cin >> a[i][j];
			a[j][i] = a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int l = 0; l + i <= n; l++) {
			int r = l + i;
			if (r - l == 1) {
				D[l][r] = 0;
			} else {
				D[l][r] = 1e18;
				for (int m = l + 1; m < r; m++) {
					D[l][r] = min(D[l][m] + E[m][r] + max(0ll, a[l][m]), D[l][r]);
				}
			}
			E[l][r] = D[l][r];
			for (int x = r; x < n; x++) {
				E[l][r] += max(0ll, -a[l][x]);
			}
		}
	}
	cout << E[0][n] << "\n";
}