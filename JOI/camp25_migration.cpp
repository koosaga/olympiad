#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

const int MAXT = 65571557;
struct node {
	int l, r, sum;
} tree[MAXT];

int piv;
int newnode() { return ++piv; }

void pull(int p) { tree[p].sum = tree[tree[p].l].sum + tree[tree[p].r].sum; }

void add(int s, int e, int x, int b, int p) {
	if (s == e) {
		tree[p].sum += b;
		return;
	}
	int m = (s + e) / 2;
	if (x <= m) {
		if (!tree[p].l)
			tree[p].l = newnode();
		add(s, m, x, b, tree[p].l);
	} else {
		if (!tree[p].r)
			tree[p].r = newnode();
		add(m + 1, e, x, b, tree[p].r);
	}
	pull(p);
}

int query(int s, int e, int ps, int pe, int p) {
	if (!p || e < ps || pe < s)
		return 0;
	if (s <= ps && pe <= e) {
		return tree[p].sum;
	}
	int pm = (ps + pe) / 2;
	return query(s, e, ps, pm, tree[p].l) + query(s, e, pm + 1, pe, tree[p].r);
}

void mergee(int s, int e, int p, int src) {
	if (s == e) {
		tree[p].sum += tree[src].sum;
		return;
	}
	int m = (s + e) / 2;
	if (tree[src].l) {
		if (!tree[p].l)
			tree[p].l = tree[src].l;
		else
			mergee(s, m, tree[p].l, tree[src].l);
	}
	if (tree[src].r) {
		if (!tree[p].r)
			tree[p].r = tree[src].r;
		else
			mergee(m + 1, e, tree[p].r, tree[src].r);
	}
	pull(p);
}
vector<vector<int>> gph;
vector<int> din, dout, dep;
int piv2, n;

void dfs(int x) {
	din[x] = piv2++;
	for (auto &y : gph[x]) {
		dep[y] = dep[x] + 1;
		dfs(y);
	}
	dout[x] = piv2;
}

struct jgz {
	// some aeren treap
	int rt;
	jgz() { rt = newnode(); }
	void insert(int a, int b) { add(0, n - 1, a, b, rt); }
	void merge(jgz &z) {
		mergee(0, n - 1, rt, z.rt);
		z.rt = newnode();
	}
	lint quer(int u, int v) { return query(u, v - 1, 0, n - 1, rt); }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	cr(gph, n);
	cr(din, n);
	cr(dout, n);
	cr(dep, n);
	vector<int> par(n), cnt(n);
	for (int i = 1; i < n; i++) {
		cin >> par[i];
		par[i]--;
		gph[par[i]].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		cin >> cnt[i];
	}
	dfs(0);
	int D = *max_element(all(dep)) + 1;
	vector<jgz> nodes(D);
	for (int i = 0; i < n; i++) {
		nodes[dep[i]].insert(din[i], cnt[i]);
	}
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int x, y;
			cin >> x >> y;
			if (x >= sz(nodes))
				continue;
			nodes[y].merge(nodes[x]);
		}
		if (t == 2) {
			int v, l;
			cin >> v >> l;
			v--;
			nodes[dep[v]].insert(din[v], l);
		}
		if (t == 3) {
			int p;
			cin >> p;
			p--;
			cout << nodes[dep[p]].quer(din[p], dout[p]) << "\n";
		}
	}
}