#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

void nie() {
	cout << "NIE\n";
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	assert(n > 1);
	if (n == 2) {
		cout << "TAK\n1 2 1557";
		return 0;
	}
	vector<array<int, 3>> a(n - 2);
	for (int i = 0; i < n - 2; i++)
		cin >> a[i][0];
	for (int i = 0; i < n - 2; i++)
		cin >> a[i][1];
	for (int i = 0; i < n - 2; i++)
		a[i][2] = i + 2;
	for (auto &v : a) {
		tie(v[0], v[1]) = make_pair(v[0] - v[1], v[0] + v[1]);
	}
	sort(all(a));
	for (int i = 1; i < n - 2; i++) {
		if ((a[i - 1][0] & 1) != (a[i][0] & 1))
			nie();
	}
	set<int> abses;
	for (auto &x : a) {
		abses.insert(abs(x[0]));
	}
	auto pe = [&](int u, int v, int w) { cout << u << " " << v << " " << w << "\n"; };
	if (sz(abses) == 1) {
		int d = *abses.begin();
		if (d == 0) {
			int w = a[0][1] / 2;
			if (w == 0)
				nie();
			if (sz(a) >= 2 && a[1][1] == 2 * w)
				nie();
			cout << "TAK\n";
			pe(1, a[0][2], w);
			pe(n, a[0][2], w);
			for (int i = 1; i < sz(a); i++) {
				pe(a[0][2], a[i][2], (a[i][1] / 2) - w);
			}
			return 0;
		} else {
			cout << "TAK\n";
			pe(1, n, d);
			for (int i = 0; i < sz(a); i++) {
				if (a[i][0] == -d) {
					pe(1, a[i][2], (a[i][1] - d) / 2);
				} else {
					pe(n, a[i][2], (a[i][1] - d) / 2);
				}
			}
			return 0;
		}
	} else {
		int d = 2e9;
		for (auto &[x, y, i] : a) {
			d = min(d, y);
		}
		vector<array<int, 3>> edges;
		int pv = 1, pd = -d;
		for (int i = 0; i < sz(a);) {
			int j = i;
			while (j < sz(a) && a[i][0] == a[j][0])
				j++;
			int repr_len = (abs(a[i][0]) == d ? d : a[i][1]);
			int repr_pos = (abs(a[i][0]) == d ? (a[i][0] > 0 ? n : 1) : a[i][2]);
			if (repr_len != d) {
				nie();
			}
			if (pd != a[i][0]) {
				edges.push_back({pv, repr_pos, -(pd - a[i][0]) / 2});
				pd = a[i][0];
				pv = a[i][2];
			}
			for (int k = i; k < j; k++) {
				if (a[k][2] != repr_pos && a[k][1] == repr_len)
					nie();
				if (a[k][2] != repr_pos)
					edges.push_back({repr_pos, a[k][2], (a[k][1] - repr_len) / 2});
			}
			i = j;
		}
		if (pd != d) {
			edges.push_back({pv, n, (d - pd) / 2});
		}
		cout << "TAK\n";
		for (auto &[u, v, w] : edges)
			pe(u, v, w);
	}
}