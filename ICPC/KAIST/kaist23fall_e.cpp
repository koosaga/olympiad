#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using llf = long double;
const int MAXN = 100005;
const int MAXT = 270000;

vector<int> gph[MAXN];
int chn[MAXN], din[MAXN], dout[MAXN], par[17][MAXN], dep[MAXN], sub[MAXN], rev[MAXN], piv;

void dfs(int x) {
	sub[x] = 1;
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		par[0][y] = x;
		dep[y] = dep[x] + 1;
		dfs(y);
		sub[x] += sub[y];
	}
}

void hld(int x) {
	din[x] = piv++;
	rev[din[x]] = x;
	if (sz(gph[x])) {
		sort(all(gph[x]), [&](int p, int q) { return sub[p] > sub[q]; });
		chn[gph[x][0]] = chn[x];
		hld(gph[x][0]);
		for (int i = 1; i < sz(gph[x]); i++) {
			chn[gph[x][i]] = gph[x][i];
			hld(gph[x][i]);
		}
	}
	dout[x] = piv;
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(u, v);
	int dx = dep[v] - dep[u];
	for (int i = 0; dx; i++) {
		if (dx & 1) {
			v = par[i][v];
		}
		dx >>= 1;
	}
	if (u == v)
		return u;
	for (int i = 16; i >= 0; i--) {
		if (par[i][u] != par[i][v]) {
			u = par[i][u];
			v = par[i][v];
		}
	}
	return par[0][u];
}

struct bit {
	lint tree[MAXN];
	void add(int x, lint v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	lint query(int x) {
		lint ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

struct node {
	lint lazy;
	int actives;
	pi subMin;
	node operator+(const node &nd) const { return node{0, actives + nd.actives, min(subMin, nd.subMin)}; }
} tree[MAXT];

void lazydown(int p) {
	for (int i = 2 * p; i < 2 * p + 2; i++) {
		tree[i].lazy += tree[p].lazy;
		tree[i].subMin[0] += tree[p].lazy;
	}
	tree[p].lazy = 0;
}

void init(int s, int e, int p) {
	if (s == e) {
		tree[p].subMin = {lint(1e18), s};
		return;
	}
	int m = (s + e) / 2;
	init(s, m, 2 * p);
	init(m + 1, e, 2 * p + 1);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void add(int s, int e, int ps, int pe, int p, lint v) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e) {
		tree[p].lazy += v;
		tree[p].subMin[0] += v;
		return;
	}
	lazydown(p);
	int pm = (ps + pe) / 2;
	add(s, e, ps, pm, 2 * p, v);
	add(s, e, pm + 1, pe, 2 * p + 1, v);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

node query(int s, int e, int ps, int pe, int p) {
	if (e < ps || pe < s)
		return node{0, 0, pi{lint(1e18), 0}};
	if (s <= ps && pe <= e)
		return tree[p];
	lazydown(p);
	int pm = (ps + pe) / 2;
	return query(s, e, ps, pm, 2 * p) + query(s, e, pm + 1, pe, 2 * p + 1);
}

void upd(int pos, int s, int e, int p, node v) {
	if (s == e) {
		tree[p] = v;
		return;
	}
	int m = (s + e) / 2;
	lazydown(p);

	if (pos <= m)
		upd(pos, s, m, 2 * p, v);
	else
		upd(pos, m + 1, e, 2 * p + 1, v);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0);
	hld(0);
	for (int i = 1; i < 17; i++) {
		for (int j = 0; j < n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	unsigned long long ans = 0;
	vector<lint> cum(n);  // only maintain for non-heavy
	vector<int> child(n); // if not heavy, din -> din
	auto INIT = [&](int n) { init(0, n - 1, 1); };
	auto RANGE_ADD = [&](int s, int e, lint x) { add(s, e, 0, n - 1, 1, x); };
	auto RANGE_ACTIVE = [&](int s, int e) { return query(s, e, 0, n - 1, 1).actives; };
	auto QUERY = [&](int s, int e) { return query(s, e, 0, n - 1, 1).subMin; };
	auto ACTIVATE = [&](int x, lint v) { upd(x, 0, n - 1, 1, node{0, 1, pi{v, x}}); };
	auto DEACTIVATE = [&](int x) { upd(x, 0, n - 1, 1, node{0, 0, pi{lint(1e18), x}}); };
	INIT(n);
	auto proc_path = [&](int l, int r, lint x, bool do_head) {
		bit.add(l + 1, +x);
		bit.add(r + 1, -x);
		RANGE_ADD(l + 1, r, -x);
		ans += x * RANGE_ACTIVE(l + 1, r);
		while (true) {
			auto it = QUERY(l + 1, r);
			if (it[0] >= 0)
				break;
			ans += it[0];
			DEACTIVATE(it[1]);
		}
		if (do_head) {
			int j = par[0][rev[l]];
			cum[l] += x;
			if (RANGE_ACTIVE(din[j] + 1, din[j] + 1) == 0) {
				ans += x;
				lint q = bit.query(din[j] + 1);
				if (q < cum[l]) {
					ans += q - cum[l];
					ACTIVATE(din[j] + 1, cum[l] - q);
					child[din[j]] = l;
				}
			} else if (child[din[j]] != l) {
				ans += x;
				if (cum[child[din[j]]] < cum[l]) {
					RANGE_ADD(din[j] + 1, din[j] + 1, cum[l] - cum[child[din[j]]]);
					ans += cum[child[din[j]]] - cum[l];
					child[din[j]] = l;
				}
			} else {
				RANGE_ADD(din[j] + 1, din[j] + 1, x);
			}
		}
	};
	auto add = [&](int u, int v, lint x) {
		while (chn[u] != chn[v]) {
			proc_path(din[chn[u]], din[u], x, true);
			u = par[0][chn[u]];
		}
		proc_path(din[v], din[u], x, false);
	};
	while (q--) {
		int u, v, x;
		cin >> u >> v >> x;
		u--;
		v--;
		int l = lca(u, v);
		add(u, l, x);
		add(v, l, x);
		cout << ans << "\n";
	}
}