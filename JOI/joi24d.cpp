#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 1050000;

struct maxseg {
	int tree[MAXT], lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		fill(tree, tree + MAXT, -1e9);
	}
	void upd(int x, int v) {
		x += lim;
		tree[x] = max(tree[x], v);
		while (x > 1) {
			x >>= 1;
			tree[x] = max(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int query(int s, int e) {
		int ret = -1e9;
		s += lim;
		e += lim;
		while (s < e) {
			if (s % 2 == 1)
				ret = max(ret, tree[s++]);
			if (e % 2 == 0)
				ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = max(ret, tree[s]);
		return ret;
	}
} maxseg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> y, y--;
	for (auto &[x, y] : a)
		cin >> x, x--;
	vector<array<lint, 3>> intv(n);
	vector<pi> ord(2 * n);
	for (int i = 0; i < n; i++) {
		ord[a[i][0]] = pi{i, 0};
		ord[a[i][1]] = pi{i, 1};
	}
	maxseg.init(n);
	for (int i = 2 * n - 1; i >= 0; i--) {
		if (ord[i][1] == 0) {
			int is = ord[i][0], ie = n;
			while (is != ie) {
				int m = (is + ie) / 2;
				if (-maxseg.query(ord[i][0] + 1, m) > a[ord[i][0]][1])
					is = m + 1;
				else
					ie = m;
			}
			intv[ord[i][0]][1] = is;
			is = 0, ie = ord[i][0];
			while (is != ie) {
				int m = (is + ie) / 2;
				if (-maxseg.query(m, ord[i][0] - 1) > a[ord[i][0]][1])
					ie = m;
				else
					is = m + 1;
			}
			intv[ord[i][0]][0] = is - 1;
			intv[ord[i][0]][2] = ord[i][0];
			//	cout << intv[ord[i][0]][0] << " " << intv[ord[i][0]][1] << " " << intv[ord[i][0]][2] << endl;
		} else {
			maxseg.upd(ord[i][0], -a[ord[i][0]][0]);
		}
	}
	int q;
	cin >> q;
	vector<array<int, 3>> queries;
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		queries.push_back({l, r, i});
	}
	vector<int> ans(q);
	int j = 0;
	sort(all(queries));
	sort(all(intv));
	maxseg.init(n);
	for (auto &[l, r, i] : queries) {
		while (j < sz(intv) && intv[j][0] < l) {
			maxseg.upd(intv[j][2], intv[j][1]);
			j++;
		}
		ans[i] = (maxseg.query(l, r - 1) < r);
	}
	for (int i = 0; i < q; i++) {
		cout << (ans[i] ? "Yes" : "No") << "\n";
	}
}