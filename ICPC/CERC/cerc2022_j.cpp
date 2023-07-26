#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530000;

__int128 ccw(pi a, pi b, pi c) {
	for (int i = 0; i < 2; i++) {
		b[i] -= a[i];
		c[i] -= a[i];
	}
	return (__int128)b[0] * c[1] - (__int128)c[0] * b[1];
}

struct seg {
	vector<pi> tree[MAXT];
	int lim;
	void init(int n, vector<pi> &a) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		for (int i = 1; i <= n; i++) {
			for (int j = i + lim; j; j >>= 1) {
				tree[j].push_back(a[i]);
			}
		}
		for (int i = 0; i < MAXT; i++) {
			vector<pi> cvxh;
			for (auto &j : tree[i]) {
				while (sz(cvxh) >= 2 && ccw(cvxh[sz(cvxh) - 2], cvxh.back(), j) <= 0)
					cvxh.pop_back();
				cvxh.push_back(j);
			}
			tree[i] = cvxh;
		}
	}
	lint query(int s, int e, pi p) {
		s += lim;
		e += lim;
		lint ret = 1e18;
		auto f = [&](int nd) {
			if (sz(tree[nd]) == 0)
				return lint(1e18);
			int l = 0, r = sz(tree[nd]) - 1;
			while (l != r) {
				int m = (l + r) / 2;
				if (ccw(p, tree[nd][m], tree[nd][m + 1]) > 0)
					r = m;
				else
					l = m + 1;
			}
			if (tree[nd][l][1] < p[1])
				return -1ll;
			return (tree[nd][l][1] - p[1]) / (tree[nd][l][0] - p[0]);
		};
		while (s < e) {
			if (s % 2 == 1)
				ret = min(ret, f(s++));
			if (e % 2 == 0)
				ret = min(ret, f(e--));
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = min(ret, f(s));
		return ret;
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<lint> sum(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> sum[i];
		sum[i] += sum[i - 1];
	}
	vector<pi> a(n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = pi{i, sum[i]};
	}
	seg.init(n, a);
	for (int i = 0; i < q; i++) {
		int l, k;
		cin >> l >> k;
		int r = l + k - 1;
		lint ans = seg.query(l, r, pi{l - 1, sum[l - 1]});
		if (ans < 0)
			cout << "stay with parents";
		else
			cout << ans;
		cout << "\n";
	}
}