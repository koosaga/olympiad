#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		// cout << "uni " << p << " " << q << endl;
		pa[q] = p;
		return 1;
	}
} dsu;

const int MAXT = 530000;

struct seg {
	int tree[MAXT], lazy[MAXT], lval[MAXT];
	void init() {
		memset(tree, 0, sizeof(tree));
		memset(lazy, -1, sizeof(lazy));
		memset(lval, -1, sizeof(lval));
	}
	void App(int p, int v) {
		assert(v != -1);
		if (tree[p] == 0)
			return;
		if (~lazy[p]) {
			dsu.uni(v, lazy[p]);
		}
		lazy[p] = v;
		if (~lval[p]) {
			dsu.uni(v, lval[p]);
		}
	}
	void lazydown(int p) {
		if (~lazy[p]) {
			for (int i = 2 * p; i < 2 * p + 2; i++) {
				App(i, lazy[p]);
			}
			lazy[p] = -1;
		}
	}
	void upd(int pos, int s, int e, int p, int v) {
		if (s == e) {
			tree[p] = (v != -1);
			lval[p] = v;
			lazy[p] = -1;
			// cout << "set " << pos << " " << v << endl;
			return;
		}
		lazydown(p);
		int m = (s + e) / 2;
		if (pos <= m)
			upd(pos, s, m, 2 * p, v);
		else
			upd(pos, m + 1, e, 2 * p + 1, v);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	void merge(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			//	cout << "merge " << ps << " " << pe << " " << v << endl;
			App(p, v);
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		merge(s, e, ps, pm, 2 * p, v);
		merge(s, e, pm + 1, pe, 2 * p + 1, v);
	}
} seg;

void solve_line_segment(vector<array<int, 4>> xseg, vector<array<int, 4>> yseg, int w, int h) {
	vector<vector<array<int, 3>>> ev_line(w + 1);
	vector<vector<array<int, 2>>> ev_inst(w + 1), ev_dele(w + 1);
	for (auto &[p, l, r, i] : xseg)
		ev_line[p].push_back({l, r, i});
	for (auto &[p, l, r, i] : yseg) {
		ev_inst[l].push_back({p, i});
		ev_dele[r].push_back({p, i});
	}
	seg.init();
	for (int i = 0; i <= w; i++) {
		for (auto &[pos, idx] : ev_dele[i]) {
			seg.upd(pos, 0, h + 1, 1, -1);
		}
		for (auto &[pos, idx] : ev_inst[i]) {
			seg.upd(pos, 0, h + 1, 1, idx);
		}
		for (auto &[l, r, idx] : ev_line[i]) {
			seg.merge(l, r - 1, 0, h + 1, 1, idx);
		}
	}
}

vector<array<int, 4>> norm(vector<array<int, 4>> a) {
	sort(all(a));
	return a;
}

void find_union(int N, vector<int> A, vector<int> B, vector<int> C, vector<int> D) {
	dsu.init(N);
	// line segment case
	{
		vector<array<int, 4>> xseg, yseg;
		for (int i = 0; i < N; i++) {
			C[i]++;
			D[i]++;
			xseg.push_back({A[i], B[i], D[i], i});
			yseg.push_back({B[i], A[i], C[i], i});
			xseg.push_back({C[i] - 1, B[i], D[i], i});
			yseg.push_back({D[i] - 1, A[i], C[i], i});
		}
		solve_line_segment(norm(xseg), norm(yseg), 2 * N + 5, 2 * N + 5);
	}
}

struct bit {
	int tree[MAXT];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXT; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, t;
	cin >> n >> t;
	vector<int> A(n), B(n), C(n), D(n);
	vector<array<int, 3>> evt(2 * n);
	for (int i = 0; i < n; i++) {
		cin >> A[i] >> B[i] >> C[i] >> D[i];
		A[i]--;
		B[i]--;
		C[i]--;
		D[i]--;
		evt[A[i]] = {B[i], D[i], i};
		evt[C[i]] = {B[i], D[i], ~i};
	}
	find_union(n, A, B, C, D);
	lint ans = 0;
	vector<int> chk(n), mark(n);
	pi counts = {0, 0};
	for (int i = 0; i < 2 * n; i++) {
		if (evt[i][2] < 0) {
			bit.add(evt[i][0], -1);
			bit.add(evt[i][1], -1);
		}
		int r = bit.query(evt[i][1] - 1);
		int l = bit.query(evt[i][0]);
		ans += r - l;
		counts[r % 2]++;
		counts[l % 2]++;
		if (evt[i][2] >= 0) {
			chk[evt[i][2]] = l % 2;
			bit.add(evt[i][0], +1);
			bit.add(evt[i][1], +1);
		}
	}
	lint black = (counts[0] - counts[1] + ans * 2) / 4;
	lint white = (counts[1] - counts[0] + ans * 2) / 4 + 1;
	for (int i = 0; i < 2 * n; i++) {
		if (evt[i][2] >= 0 && !mark[dsu.find(evt[i][2])]) {
			mark[dsu.find(evt[i][2])] = true;
			if (chk[evt[i][2]])
				black++;
			else
				white++;
		}
	}
	if (t == 1)
		cout << black + white << "\n";
	else
		cout << white << " " << black << "\n";
}