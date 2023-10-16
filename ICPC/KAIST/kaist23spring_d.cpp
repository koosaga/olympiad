#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

lint udiv(lint x, lint y) { return (x + y - 1) / y; }
lint ans[5005][5005];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;

	int q;
	cin >> q;
	vector<pi> a(n);
	vector<int> g(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
		if (i)
			g[i] = a[i][0] - a[i - 1][1];
	}
	for (int i = 1; i < n; i++) {
		lint sum = 0;
		for (int j = i; j < n; j++) {
			sum += g[j];
			ans[i - 1][j] = max(ans[i - 1][j], udiv(sum, j - i + 2));
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			ans[i][j] = max({ans[i][j], ans[i + 1][j], ans[i][j - 1]});
		}
	}
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << ans[l - 1][r - 1] << "\n";
	}
}