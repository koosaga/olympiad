#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 15557;

struct bit {
	pi tree[MAXN];
	void init() { fill(tree, tree + MAXN, pi{0, 0}); }
	void add(int x, pi v) {
		for (int i = x + 2; i < MAXN; i += i & -i) {
			tree[i][0] += v[0];
			tree[i][1] += v[1];
		}
	}
	pi query(int x) {
		pi ret{0, 0};
		for (int i = x + 2; i; i -= i & -i) {
			ret[0] += tree[i][0];
			ret[1] += tree[i][1];
		}
		return ret;
	}
} bit;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	string s;
	cin >> s;
	int n = sz(s);
	lint ret = 0;
	vector<int> gidx, sum(sz(s) + 1);
	for (int i = 0; i < sz(s); i++) {
		if (s[i] == 'G')
			gidx.push_back(i);
		sum[i + 1] = sum[i] + (s[i] == 'G');
	}
	for (int d = 1; d <= sz(s); d++) {
		for (int i = 0; i + d <= sz(s); i++) {
			int j = i + d;
			int l = sum[i], r = sum[j];
			if ((r - l) % 2 && (j - i) % 2 == 0)
				ret -= 1;
			else {
				int d = (r - l) / 2;
				int p = i + j - 1;
				if ((r - l) % 2 == 1) {
					ret += abs(p / 2 - gidx[l + d]);
				}
			}
		}
	}
	for (int i = 0; i < 2 * sz(gidx) - 1; i++) {
		int s = i / 2, e = (i + 1) / 2;
		if (s == e)
			s--, e++;
		bit.init();
		int k = 0;
		pi g{0, 0};
		while (s >= 0 && e < sz(gidx)) {

			int pos = gidx[s] + gidx[e];
			bit.add(pos, pi{-2 * pos, 2});
			g[0] += pos;
			g[1] -= 1;

			int i1 = (s > 0 ? gidx[s - 1] : -1);
			int i2 = gidx[s];
			int j1 = gidx[e];
			int j2 = (e + 1 < sz(gidx) ? gidx[e + 1] : n);

			for (int x = i1 + 1; x <= i2; x++) {
				for (int y = j1 + 1; y <= j2; y++) {
					if ((y - x) % 2 == 0 && (i % 2 == 0))
						continue;
					int qpos = x + y - 1;
					auto ans = bit.query(qpos);
					ans[0] += g[0];
					ans[1] += g[1];
					ret += ans[0] + 1ll * ans[1] * qpos;
				}
			}

			s--;
			e++;
		}
	}
	cout << ret << "\n";
}