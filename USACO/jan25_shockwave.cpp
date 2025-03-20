#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

lint solve() {
	int n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	__int128 amin, amax;
	auto trial = [&](__int128 t) {
		amin = 0, amax = t;
		for (int i = 0; i < n; i++) {
			if (a[i] <= 0)
				continue;
			if (2 * i == n - 1) {
				if (a[i] > t * (n - 1) / 2)
					return false;
			}
			if (2 * i < n - 1) {
				__int128 g = t * (n - 1 - i) - a[i];
				__int128 h = n - 1 - 2 * i;
				if (g < 0)
					return false;
				amax = min(amax, g / h);
			}
			if (2 * i > n - 1) {
				__int128 g = a[i] - t * (n - 1 - i);
				__int128 h = 2 * i - n + 1;
				if (g >= 0)
					amin = max(amin, (g + h - 1) / h);
			}
		}
		return amin <= amax;
	};
	lint s = 0, e = 2e18;
	while (s != e) {
		lint m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m + 1;
	}
	if (s <= 1)
		return s;
	trial(s - 1);
	vector<int> cnt(n + 1);
	lint A = amax, B = s - 2 - amax;
	for (int i = 0; i < n; i++) {
		a[i] -= A * i + B * (n - 1 - i);
		if (a[i] > 0) {
			lint l = i - a[i] + 1;
			lint r = i + a[i] - 1;
			l = max(l, 0ll);
			r = min(r + 1, 1ll * n);
			cnt[l]++;
			cnt[r]--;
		}
	}
	for (int i = 0; i < n; i++) {
		if (cnt[i] == 0)
			return s - 1;
		cnt[i + 1] += cnt[i];
	}
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cout << solve() << "\n";
	}
}