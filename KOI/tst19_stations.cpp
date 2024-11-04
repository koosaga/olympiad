#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 125;

lint L[MAXN][MAXN][MAXN], R[MAXN][MAXN][MAXN];
lint f[MAXN][MAXN], foo[MAXN];

int isqrt(int x) {
	if (x == 0)
		return 0;
	int z = (int)sqrt(x) + 3;
	while (z * z > x)
		z--;
	return z;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int d = abs(a[i] - a[j]);
			f[i][j] = 1ll * d * isqrt(d);
		}
	}
	memset(L, 0x3f, sizeof(R));
	memset(R, 0x3f, sizeof(R));
	for (int i = 0; i < n; i++) {
		L[0][i][i + 1] = R[0][i][i + 1] = 0;
	}
	for (int i = 1; i < n; i++) {
		for (int l = 0; l <= n; l++) {
			memset(foo, 0x3f, sizeof(foo));
			for (int r = l + 1; r <= n; r++) {
				if (r - l == 1) {
					R[i][l][r] = 0;
				} else {
					for (int b = l + 1; b < r; b++) {
						R[i][l][r] = min(R[i][l][r], foo[b + 1] + R[i - 1][b][r] + f[b][l]);
					}
				}
				for (int b = r; b < n; b++) {
					foo[b + 1] = min(foo[b + 1], R[i][l][r] + L[i - 1][r][b + 1]);
				}
			}
		}
		for (int r = 0; r <= n; r++) {
			memset(foo, 0x3f, sizeof(foo));
			for (int l = r - 1; l >= 0; l--) {
				if (r - l == 1) {
					L[i][l][r] = 0;
				} else {
					for (int a = l; a < r; a++) {
						L[i][l][r] = min(L[i][l][r], L[i - 1][l][a + 1] + foo[a] + f[a][r - 1]);
					}
				}
				for (int a = 0; a < l; a++)
					foo[a] = min(foo[a], R[i - 1][a][l] + L[i][l][r]);
			}
		}
		lint ans = 1e18;
		for (int j = 0; j < n; j++)
			ans = min(ans, L[i][0][j + 1] + R[i][j][n]);
		cout << ans << "\n";
	}
}