#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc = 1;
	//	cin >> tc;
	while (tc--) {
		int n, q;
		cin >> n >> q;
		q--;
		vector<int> a(n), b(n), ra(n), rb(n);
		for (int i = 0; i < n; i++) {
			int p;
			cin >> p;
			a[p - 1] = i;
			ra[i] = p - 1;
		}
		for (int i = 0; i < n; i++) {
			cin >> b[i];
			b[i]--;
			rb[b[i]] = i;
		}
		vector<int> fuck(n - 1);
		for (int i = 0; i < n - 1; i++)
			if (a[b[i]] > a[b[i + 1]])
				fuck[i] = 1;
		lint cnt = accumulate(all(fuck), 0);
		auto upd = [&](int p, int v) {
			if (p + 1 < n)
				cnt -= fuck[p];
			if (p > 0)
				cnt -= fuck[p - 1];
			if (p + 1 < n)
				fuck[p] = (a[b[p]] > a[b[p + 1]]);
			if (p > 0)
				fuck[p - 1] = (a[b[p - 1]] > a[b[p]]);
			if (p + 1 < n)
				cnt += fuck[p];
			if (p > 0)
				cnt += fuck[p - 1];
		};
		cout << 1ll * (cnt - 1) * n + a[b.back()] + 1 << "\n";
		while (q--) {
			int t, x, y;
			cin >> t >> x >> y;
			x--;
			y--;
			if (t == 1) {
				swap(ra[x], ra[y]);
				swap(a[ra[x]], a[ra[y]]);
				upd(rb[ra[x]], +1);
				upd(rb[ra[y]], +1);
			}
			if (t == 2) {
				swap(b[x], b[y]);
				swap(rb[b[x]], rb[b[y]]);
				upd(x, +1), upd(y, +1);
			}
			cout << 1ll * (cnt - 1) * n + a[b.back()] + 1 << "\n";
		}
	}
}