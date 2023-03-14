#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXT = 1050000;
const lint inf = 4e18;

struct line {
	lint A, B;
	lint eval(lint x) { return A * x + B; }
	// returns the x-intercept of intersection "strictly" larger than T
	lint cross_after(line &x, lint T) {
		if (x.A == A) {
			return inf;
		}
		lint up = x.B - B;
		lint dn = A - x.A;
		if (dn < 0) {
			dn *= -1;
			up *= -1;
		}
		lint incep = (up <= 0 ? -((-up) / dn) : (up + dn - 1) / dn);
		if (incep > T)
			return incep;
		return inf;
	}
};

struct kst { // min kinetic segment tree
	line tree[MAXT];
	lint melt[MAXT], T;
	int n;
	bool cmp(line &a, line &b) {
		lint l = a.eval(T), r = b.eval(T);
		if (l != r)
			return l < r;
		return a.A < b.A;
	}
	void pull(int p) {
		tree[p] = cmp(tree[2 * p], tree[2 * p + 1]) ? tree[2 * p] : tree[2 * p + 1];
		melt[p] = min({melt[2 * p], melt[2 * p + 1], tree[2 * p].cross_after(tree[2 * p + 1], T)});
	}
	void init(int s, int e, int p, vector<line> &l) {
		if (s == e) {
			tree[p] = l[s];
			melt[p] = inf;
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2 * p, l);
		init(m + 1, e, 2 * p + 1, l);
		pull(p);
	}
	void update(int pos, line v, int s, int e, int p = 1) {
		if (s == e) {
			tree[p] = v;
			return;
		}
		int m = (s + e) / 2;
		if (pos <= m)
			update(pos, v, s, m, 2 * p);
		else
			update(pos, v, m + 1, e, 2 * p + 1);
		pull(p);
	}
	lint query(int s, int e, int ps, int pe, int p = 1) {
		if (e < ps || pe < s)
			return inf;
		if (s <= ps && pe <= e)
			return tree[p].eval(T);
		int pm = (ps + pe) / 2;
		return min(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
	}
	void heaten(int s, int e, int p) {
		if (melt[p] > T)
			return;
		int m = (s + e) / 2;
		heaten(s, m, 2 * p);
		heaten(m + 1, e, 2 * p + 1);
		pull(p);
	}
	void init(vector<line> &l, lint _T) {
		n = sz(l);
		T = _T;
		init(0, n - 1, 1, l);
	}
	void heaten(lint _T) {
		assert(T <= _T);
		T = _T;
		heaten(0, n - 1, 1);
	}
} kst;

struct query {
	int num, pos, idx;
	bool operator<(const query &q) const { return pos < q.pos; }
};

struct event {
	int pos, idx;
	line val;
	bool operator<(const event &e) const { return pos < e.pos; }
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<event> v;
	for (int i = 0; i < n; i++) {
		int l, r;
		lint A, B;
		cin >> l >> r >> A >> B;
		v.push_back({l, i, {A, B}});
		v.push_back({r, i, {0ll, inf}});
	}
	vector<query> Q;
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		if (t == 0) {
			int l, r;
			lint A, B;
			cin >> l >> r >> A >> B;
			v.push_back({l, n, {A, B}});
			v.push_back({r, n, {0ll, inf}});
			n++;
		} else {
			int x;
			cin >> x;
			int idx = sz(Q);
			Q.push_back({n, x, idx});
		}
	}
	sort(all(v));
	sort(all(Q));
	vector<lint> ret(sz(Q));
	vector<line> a(n, (line){0, inf});
	kst.init(a, -2e9);
	int j = 0;
	for (int i = 0; i < sz(Q); i++) {
		while (j < sz(v) && v[j].pos <= Q[i].pos) {
			kst.heaten(v[j].pos);
			kst.update(v[j].idx, v[j].val, 0, n - 1);
			j++;
		}
		kst.heaten(Q[i].pos);
		ret[Q[i].idx] = kst.query(0, Q[i].num - 1, 0, n - 1, 1);
	}
	for (auto &x : ret) {
		if (x > 0.6 * inf)
			cout << "INFINITY\n";
		else
			cout << x << "\n";
	}
}