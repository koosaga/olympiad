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
	int n, l;
	cin >> n >> l;
	vector<array<int, 3>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i][1];
		a[i][2] = i;
	}
	int p, q;
	cin >> p >> q;
	p--;
	if (q + a[p][1] > l) {
		cout << "NO\n";
		return 0;
	}
	int crit = l;
	for (int i = 0; i < n; i++)
		crit -= a[i][1];
	if (a[p][1] <= crit) {
		int s = q, e = q + a[p][1];
		sort(all(a));
		int cs = 0, ce = l;
		for (int j = 0; j < n; j++)
			if (a[j][1] > crit)
				ce -= a[j][1];
		if (cs <= s && e <= ce) {
			cout << "YES\n";
			return 0;
		}
		for (int j = 0; j < n; j++) {
			if (a[j][1] > crit) {
				cs += a[j][1];
				ce += a[j][1];
				if (cs <= s && e <= ce) {
					cout << "YES\n";
					return 0;
				}
			}
		}
		cout << "NO\n";
		return 0;
	}
	int lb = 0, rb = l;
	for (int i = 0; i < n; i++) {
		if (a[i][1] > crit && i != p) {
			if (a[i][0] < a[p][0])
				lb += a[i][1];
			else
				rb -= a[i][1];
		}
	}
	cout << (lb <= q && q + a[p][1] <= rb ? "YES" : "NO") << "\n";
}