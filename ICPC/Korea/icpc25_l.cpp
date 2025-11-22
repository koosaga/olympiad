#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	int lmax = -1e9, rmin = 1e9;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		int z;
		cin >> z;
		lmax = max(lmax, l);
		rmin = min(rmin, r);
	}
	while (q--) {
		int x;
		cin >> x;
		cout << max({0, lmax - x, x - rmin}) << "\n";
	}
}