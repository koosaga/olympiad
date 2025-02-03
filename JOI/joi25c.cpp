#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 1050000;

struct seg {
	lint tree[MAXT], lim;
	void init(vector<pi> &a) {
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		memset(tree, 0x3f, sizeof(tree));
		for (int i = 0; i < sz(a); i++)
			tree[i + lim] = a[i][1] - a[i][0];
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	lint query(int l, int r) {
		l += lim;
		r += lim;
		lint ret = 1e18;
		while (l < r) {
			if (l % 2 == 1)
				ret = min(ret, tree[l++]);
			if (r % 2 == 0)
				ret = min(ret, tree[r--]);
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			ret = min(ret, tree[l]);
		return ret;
	}
} seg;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, p;
	cin >> n >> m >> p;
	vector<pi> points, valid;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		points.push_back({c, b - 2});
	}
	sort(all(points));
	n--;
	vector<int> counts(n);
	int ons = 0, j = 0;
	for (int i = 0; i < sz(points); i++) {
		while (j < sz(points) && ons < n) {
			if (counts[points[j][1]] == 0)
				ons++;
			counts[points[j][1]]++;
			j++;
		}
		if (ons == n) {
			valid.push_back({points[i][0], points[j - 1][0]});
		}
		counts[points[i][1]]--;
		if (counts[points[i][1]] == 0)
			ons--;
	}
	seg.init(valid);
	int q;
	cin >> q;
	while (q--) {
		int l, r, x;
		cin >> l >> r >> x;
		int i1 = lower_bound(all(valid), pi{l - x, -1}, [&](pi a, pi b) { return a[0] < b[0]; }) - valid.begin();
		int i2 = upper_bound(all(valid), pi{-1, r + x}, [&](pi a, pi b) { return a[1] < b[1]; }) - valid.begin();
		cout << ((seg.query(i1, i2 - 1) <= r - l + x) ? "Yes" : "No") << "\n";
	}
}