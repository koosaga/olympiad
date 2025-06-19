#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	lint sum = accumulate(all(a), 0ll);
	vector<lint> ans(n + 1);
	lint g = a[0];
	for (int i = 1; i <= n; i++) {
		if (i == n || gcd(g, a[i]) != g) {
			// at most one set with nontrivial gcd, and that set contains min
			lint cur = g + sum;
			int cnt = n;
			for (int j = 0; j < n; j++) {
				if (a[j] % g == 0 || (j > 0 && a[j - 1] == a[j])) {
					cur -= a[j];
					ans[cnt] = max(ans[cnt], cur);
					cnt--;
				}
			}
		}
		if (i < n)
			g = gcd(g, a[i]);
	}

	for (int i = 1; i <= n; i++)
		cout << ans[i] << "\n";
}