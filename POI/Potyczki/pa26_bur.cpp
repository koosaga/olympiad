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
	int n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	lint sum = accumulate(all(a), 0ll);
	for (int k = n; k >= 1; k--) {
		if (sum % k)
			continue;
		vector<lint> sub(n + 1);
		lint currents = 0;
		bool ok = 1;
		for (int j = 0; j < n; j++) {
			currents -= sub[j];
			if (currents > a[j]) {
				ok = 0;
				break;
			}
			if (currents < 0) {
				ok = 0;
				break;
			}
			if (currents < a[j]) {
				lint d = a[j] - currents;
				if (j + k < sz(sub))
					sub[j + k] += d;
				else
					ok = 0;
				currents += d;
			}
		}
		currents -= sub[n];
		if (currents != 0)
			ok = 0;
		if (ok) {
			cout << k << "\n";
			break;
		}
	}
}