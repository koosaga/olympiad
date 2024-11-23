#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;

int a[3][MAXN];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < q; i++) {
		int l, r, c;
		cin >> l >> r >> c;
		a[c - 1][l - 1] += 1;
		a[c - 1][r] -= 1;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j <= n; j++)
			a[i][j] += a[i][j - 1];
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (a[0][i] && a[1][i] && !a[2][i])
			ans++;
	}
	cout << ans << "\n";
}