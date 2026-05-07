#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXT = 3000005;
using llf = long double;

int tree[MAXT][2], cnt[MAXT], piv;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, k;
	cin >> n >> k;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	int piv = 0;
	for (int i = 0; i < n; i++) {
		int pos = 0;
		for (int j = 29; j >= 0; j--) {
			bool b = (a[i] >> j) % 2;
			if (!tree[pos][b]) {
				tree[pos][b] = ++piv;
			}
			pos = tree[pos][b];
			cnt[pos]++;
		}
	}
	auto count = [&](int x) {
		lint ret = 0;
		for (auto &v : a) {
			int pos = 0;
			for (int j = 29; j >= 0; j--) {
				int b = (v >> j) % 2;
				if ((x >> j) % 2) {
					ret += cnt[tree[pos][b]];
					b ^= 1;
				}
				pos = tree[pos][b];
				if (!pos)
					break;
			}
			if (pos)
				ret += cnt[pos];
		}
		return ret;
	};
	lint s = 0, e = (1 << 30) - 1;
	while (s != e) {
		lint m = (s + e) / 2;
		if (count(m) < 2 * k + n)
			s = m + 1;
		else
			e = m;
	}
	cout << s << "\n";
}