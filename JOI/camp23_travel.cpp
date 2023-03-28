#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using line = array<lint, 3>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

lint g1[18][MAXN], g2[18][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	g1[0][0] = -1e18;
	g2[0][n - 1] = 1e18;
	for (int i = 0; i < n; i++) {
		if (i)
			g1[0][i] = 2 * a[i] - a[i - 1]; // mx
		if (i + 1 < n)
			g2[0][i] = 2 * a[i] - a[i + 1]; // mn
	}
	for (int i = 1; i < 18; i++) {
		for (int j = 0; j < n; j++) {
			g1[i][j] = g1[i - 1][j];
			g2[i][j] = g2[i - 1][j];
			if (j > (1 << (i - 1)))
				g1[i][j] = max(g1[i][j], g1[i - 1][j - (1 << (i - 1))]);
			if (j + (1 << (i - 1)) < n)
				g2[i][j] = min(g2[i][j], g2[i - 1][j + (1 << (i - 1))]);
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int s;
		cin >> s;
		int l = upper_bound(all(a), s) - a.begin();
		int r = l;
		lint ans = 0;
		auto leftConsume = [&](int l, int r) {
			for (int i = 17; i >= 0; i--) {
				if (l >= (1 << i) && g1[i][l] <= a[r])
					l -= (1 << i);
			}
			return l;
		};
		auto rightConsume = [&](int l, int r) {
			for (int i = 17; i >= 0; i--) {
				if (r + (1 << i) < n && a[l] < g2[i][r])
					r += (1 << i);
			}
			return r;
		};
		while (l > 0 && r < n) {
			int d1 = s - a[l - 1];
			int d2 = a[r] - s;
			if (d1 <= d2) {
				int nl = leftConsume(l - 1, r);
				ans += s - a[nl];
				l = nl;
				s = a[nl];
			} else {
				int nr = rightConsume(l - 1, r);
				ans += a[nr] - s;
				r = nr + 1;
				s = a[nr];
			}
		}
		if (l > 0) {
			ans += s - a[0];
		}
		if (r < n) {
			ans += a[n - 1] - s;
		}
		cout << ans << "\n";
	}
}