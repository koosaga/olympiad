#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint n, k;
	cin >> n >> k;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	while (k > 0) {
		sort(all(a));
		a.erase(a.begin(), lower_bound(all(a), 1));
		if (sz(a) <= 1)
			break;
		if (sz(a) == 2) {
			lint d = min(k, a[1] / a[0]);
			a[1] -= d * a[0];
			k -= d;
			continue;
		}
		if (sz(a) == 3) {
			lint ts = 0, te = min(k, lint(2e9));
			auto ok = [&](__int128 T) {
				lint x = a[0], y = a[1], z = a[2];
				if (x > y - T * x)
					return false;
				if (y - T * x > z - T * y + T * (T + 1) / 2 * x)
					return false;
				return true;
			};
			while (ts != te) {
				lint m = (1 + ts + te) / 2;
				if (ok(m))
					ts = m;
				else
					te = m - 1;
			}
			if (ts == 0) {
				for (int i = 1; i < sz(a); i++)
					a[i] -= a[i - 1];
				k--;
			} else {
				a[2] -= a[1] * ts;
				a[2] += a[0] * ts * (ts + 1) / 2;
				a[1] -= a[0] * ts;
				k -= ts;
			}
			continue;
		}
		for (int i = 1; i < sz(a); i++)
			a[i] -= a[i - 1];
		k--;
	}

	for (int i = 0; i < n - sz(a); i++)
		cout << "0 ";
	for (int i = 0; i < sz(a); i++)
		cout << a[i] << " ";
	cout << "\n";
}
