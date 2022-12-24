#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1050000;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	auto report = [&](vector<pi> v) {
		assert(sz(v) == k);
		int cur = 0;
		bool good = 0;
		for (int i = 0; i < k; i++) {
			int nxtMin = 2e9;
			for (int j = v[i][0]; j <= v[i][1]; j++) {
				if (a[j] > cur)
					nxtMin = min(nxtMin, a[j]);
			}
			if (nxtMin > 1.9e9) {
				good = 1;
				break;
			}
			cur = nxtMin;
		}
		assert(good);
		cout << "TAK\n";
		// assert(v[0][0] == 0 && v[k - 1][1] == n - 1);
		for (int i = 1; i < k; i++) {
			//	assert(v[i - 1][1] + 1 == v[i][0]);
			cout << v[i][0] << " ";
		}
		cout << "\n";
	};
	int decpos = -1;
	for (int i = 1; i < n; i++) {
		if (a[i - 1] >= a[i]) {
			decpos = i;
		}
	}
	if (decpos == -1) {
		cout << "NIE\n";
		return 0;
	}
	if (k >= 4) {
		int l = decpos - 1, r = decpos;
		int curInterval = 2 + (l > 0) + (r < n - 1);
		while (l - 1 > 0 && curInterval < k) {
			l--;
			curInterval++;
		}
		while (r + 1 < n - 1 && curInterval < k) {
			r++;
			curInterval++;
		}
		vector<pi> intv;
		if (l > 0)
			intv.push_back({0, l - 1});
		for (int i = l; i <= r; i++)
			intv.push_back({i, i});
		if (r + 1 < n)
			intv.push_back({r + 1, n - 1});
		report(intv);
		return 0;
	}
	if (k == 3) {
		int minval = *min_element(all(a));
		int maxval = *max_element(all(a));
		if (a[0] != minval) {
			int p = 0;
			while (a[p] != minval)
				p++;
			vector<pi> intv;
			if (p < n - 1) {
				intv.push_back({0, p - 1});
				intv.push_back({p, p});
				intv.push_back({p + 1, n - 1});
			} else {
				intv.push_back({0, p - 2});
				intv.push_back({p - 1, p - 1});
				intv.push_back({p, p});
			}
			report(intv);
			return 0;
		}
		if (a[n - 1] != maxval) {
			int p = n - 1;
			while (a[p] != maxval)
				p--;
			vector<pi> intv;
			if (p > 0) {
				intv.push_back({0, p - 1});
				intv.push_back({p, p});
				intv.push_back({p + 1, n - 1});
			} else {
				intv.push_back({0, 0});
				intv.push_back({1, 1});
				intv.push_back({2, n - 1});
			}
			report(intv);
			return 0;
		}
		for (int i = 1; i < n - 1; i++) {
			if (a[i] == minval || a[i] == maxval) {
				vector<pi> intv;
				intv.push_back({0, i - 1});
				intv.push_back({i, i});
				intv.push_back({i + 1, n - 1});
				report(intv);
				return 0;
			}
		}
		cout << "NIE\n";
		return 0;
	}
	assert(k == 2);
	vector<int> curmax = a;
	for (int i = n - 2; i >= 0; i--) {
		curmax[i] = max(curmax[i], curmax[i + 1]);
	}
	int curmin = 2e9;
	for (int i = 1; i < n; i++) {
		curmin = min(curmin, a[i - 1]);
		if (curmin >= curmax[i]) {
			vector<pi> intv;
			intv.push_back({0, i - 1});
			intv.push_back({i, n - 1});
			report(intv);
			return 0;
		}
	}
	cout << "NIE\n";
	return 0;
}