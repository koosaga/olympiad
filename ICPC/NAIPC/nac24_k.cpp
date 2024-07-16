#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 16666;

struct point {
	int x, y, d, idx;
};

struct node {
	int sum, pfxmin; // proper
	node() { sum = pfxmin = 0; }
	node(int x) { sum = pfxmin = x; }
	node operator+(const node &nd) const {
		node ans;
		ans.sum = sum + nd.sum;
		ans.pfxmin = min(pfxmin, sum + nd.pfxmin);
		return ans;
	}
};

struct seg {
	node tree[MAXT];
	int lim;
	int ignore;
	void init(int n) {
		ignore = n - 1;
		for (lim = 1; lim <= n; lim <<= 1)
			;
		for (int i = 0; i < lim; i++)
			tree[i + lim] = node(1);
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
	void upd(int x, int v) {
		if (x == ignore)
			return;
		x += lim;
		tree[x] = node(v);
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
} seg;

struct event {
	lint up, dn;
	int i1, i2;
	bool operator<(const event &ev) const {
		if (up * ev.dn != ev.up * dn)
			return up * ev.dn < ev.up * dn;
		if (i1 != ev.i1)
			return i1 < ev.i1;
		return i2 < ev.i2;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, w;
	cin >> n >> w;
	vector<point> v;
	for (int i = 0; i < n; i++) {
		int x, l, r;
		cin >> x >> l >> r;
		v.push_back({x, l, +1});
		v.push_back({x, r, -1});
	}
	sort(all(v), [&](const point &a, const point &b) { return a.y < b.y; });
	vector<int> rev(sz(v));
	seg.init(sz(v));
	for (int i = 0; i < sz(v); i++) {
		v[i].idx = i;
		rev[i] = i;
		seg.upd(i, v[i].d);
	}
	if (seg.tree[1].pfxmin > 0) {
		cout << "-1\n";
		return 0;
	}
	vector<event> events;
	for (int i = 0; i < sz(v); i++) {
		for (int j = i + 1; j < sz(v); j++) {
			lint x1 = v[i].x;
			lint y1 = v[i].y;
			lint x2 = v[j].x;
			lint y2 = v[j].y;
			if (x1 == x2)
				continue;
			if (x1 > x2) {
				swap(x1, x2);
				swap(y1, y2);
			}
			lint up = x2 * (y2 - y1) - y2 * (x2 - x1);
			lint dn = y2 - y1;
			if (dn < 0) {
				dn *= -1;
				up *= -1;
			}
			if (up >= 0)
				continue;
			events.push_back({up, dn, i, j});
		}
	}
	sort(all(events));
	double ret = 0;
	for (int i = 0; i < sz(events); i++) {
		swap(rev[events[i].i1], rev[events[i].i2]);
		swap(v[rev[events[i].i1]], v[rev[events[i].i2]]);
		seg.upd(rev[events[i].i1], v[rev[events[i].i1]].d);
		seg.upd(rev[events[i].i2], v[rev[events[i].i2]].d);
		//	for (int i = 0; i < sz(v); i++)
		//		cout << v[i].d << " ";
		//	cout << endl;
		double cur = 1.0 * events[i].up / events[i].dn;
		double nxt = 0;
		if (i + 1 < sz(events))
			nxt = 1.0 * events[i + 1].up / events[i + 1].dn;
		//		cout << nxt - cur << endl;
		if (seg.tree[1].pfxmin > 0) {
			ret += nxt - cur;
		}
	}
	cout << setprecision(69) << ret << "\n";
}
