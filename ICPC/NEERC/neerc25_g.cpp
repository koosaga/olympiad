#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

void solve() {
	int n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	auto trial = [&](lint x) {
		lint lo = 0, hi = 1e18;
		lint f = 0;
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				lo = max(lo, -f);
				hi = min(hi, x - f);
			} else {
				hi = min(hi, f);
				lo = max(lo, f - x);
			}
			f = a[i] - f;
			// x + f or -x + f
		}
		if (n % 2 == 0) {
			assert(f == 0);
		} else {
			assert(f % 2 == 0);
			f /= 2;
			lo = max(lo, f);
			hi = min(hi, f);
			// -x + f == x
		}
		return lo <= hi;
	};
	lint sum = accumulate(all(a), 0ll);
	assert(sum % 2 == 0);
	sum /= 2;
	sum = (sum + n - 2) / (n - 1);
	lint s = sum, e = 1e10;
	while (s != e) {
		lint m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m + 1;
	}
	cout << s << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}