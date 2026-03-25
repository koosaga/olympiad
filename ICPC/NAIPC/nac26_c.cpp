#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 500005;

namespace atcoder {

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
	unsigned int x = 1;
	while (x < (unsigned int)(n))
		x *= 2;
	return x;
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
	unsigned long index;
	_BitScanForward(&index, n);
	return index;
#else
	return __builtin_ctz(n);
#endif
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
	int x = 0;
	while (!(n & (1 << x)))
		x++;
	return x;
}
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id> struct lazy_segtree {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");
	static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>, "mapping must work as S(F, S)");
	static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
				  "composition must work as F(F, F)");
	static_assert(std::is_convertible_v<decltype(id), std::function<F()>>, "id must work as F()");

  public:
	lazy_segtree() : lazy_segtree(0) {}
	explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
	explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size())) {
		size = (int)bit_ceil((unsigned int)(_n));
		log = countr_zero((unsigned int)size);
		d = std::vector<S>(2 * size, e());
		lz = std::vector<F>(size, id());
		for (int i = 0; i < _n; i++)
			d[size + i] = v[i];
		for (int i = size - 1; i >= 1; i--) {
			update(i);
		}
	}

	void set(int p, S x) {
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--)
			push(p >> i);
		d[p] = x;
		for (int i = 1; i <= log; i++)
			update(p >> i);
	}

	S get(int p) {
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--)
			push(p >> i);
		return d[p];
	}

	S prod(int l, int r) {
		assert(0 <= l && l <= r && r <= _n);
		if (l == r)
			return e();

		l += size;
		r += size;

		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l)
				push(l >> i);
			if (((r >> i) << i) != r)
				push((r - 1) >> i);
		}

		S sml = e(), smr = e();
		while (l < r) {
			if (l & 1)
				sml = op(sml, d[l++]);
			if (r & 1)
				smr = op(d[--r], smr);
			l >>= 1;
			r >>= 1;
		}

		return op(sml, smr);
	}

	S all_prod() { return d[1]; }

	void apply(int p, F f) {
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--)
			push(p >> i);
		d[p] = mapping(f, d[p]);
		for (int i = 1; i <= log; i++)
			update(p >> i);
	}
	void apply(int l, int r, F f) {
		assert(0 <= l && l <= r && r <= _n);
		if (l == r)
			return;

		l += size;
		r += size;

		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l)
				push(l >> i);
			if (((r >> i) << i) != r)
				push((r - 1) >> i);
		}

		{
			int l2 = l, r2 = r;
			while (l < r) {
				if (l & 1)
					all_apply(l++, f);
				if (r & 1)
					all_apply(--r, f);
				l >>= 1;
				r >>= 1;
			}
			l = l2;
			r = r2;
		}

		for (int i = 1; i <= log; i++) {
			if (((l >> i) << i) != l)
				update(l >> i);
			if (((r >> i) << i) != r)
				update((r - 1) >> i);
		}
	}

	template <bool (*g)(S)> int max_right(int l) {
		return max_right(l, [](S x) { return g(x); });
	}
	template <class G> int max_right(int l, G g) {
		assert(0 <= l && l <= _n);
		assert(g(e()));
		if (l == _n)
			return _n;
		l += size;
		for (int i = log; i >= 1; i--)
			push(l >> i);
		S sm = e();
		do {
			while (l % 2 == 0)
				l >>= 1;
			if (!g(op(sm, d[l]))) {
				while (l < size) {
					push(l);
					l = (2 * l);
					if (g(op(sm, d[l]))) {
						sm = op(sm, d[l]);
						l++;
					}
				}
				return l - size;
			}
			sm = op(sm, d[l]);
			l++;
		} while ((l & -l) != l);
		return _n;
	}

	template <bool (*g)(S)> int min_left(int r) {
		return min_left(r, [](S x) { return g(x); });
	}
	template <class G> int min_left(int r, G g) {
		assert(0 <= r && r <= _n);
		assert(g(e()));
		if (r == 0)
			return 0;
		r += size;
		for (int i = log; i >= 1; i--)
			push((r - 1) >> i);
		S sm = e();
		do {
			r--;
			while (r > 1 && (r % 2))
				r >>= 1;
			if (!g(op(d[r], sm))) {
				while (r < size) {
					push(r);
					r = (2 * r + 1);
					if (g(op(d[r], sm))) {
						sm = op(d[r], sm);
						r--;
					}
				}
				return r + 1 - size;
			}
			sm = op(d[r], sm);
		} while ((r & -r) != r);
		return 0;
	}

  private:
	int _n, size, log;
	std::vector<S> d;
	std::vector<F> lz;

	void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
	void all_apply(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size)
			lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		all_apply(2 * k, lz[k]);
		all_apply(2 * k + 1, lz[k]);
		lz[k] = id();
	}
};
} // namespace atcoder

struct node {
	lint minv, mincnt;
	node() { minv = 1e9, mincnt = 0; }
	node(int x) {
		minv = 0;
		mincnt = x;
	}
	node operator+(const node &nd) {
		node ret;
		ret.minv = min(minv, nd.minv);
		ret.mincnt = 0;
		if (ret.minv == minv)
			ret.mincnt += mincnt;
		if (ret.minv == nd.minv)
			ret.mincnt += nd.mincnt;
		return ret;
	}
};

node TT(node a, node b) { return a + b; }
node UT(int a, node b) {
	b.minv += a;
	return b;
}
int UU(int a, int b) { return a + b; }
node ET() { return node(); }
int EU() { return 0; }

lint solve(vector<lint> a, vector<pi> b) {
	int n = sz(a);
	vector<vector<pi>> sweeps(n);
	for (int i = 0; i < sz(b); i++) {
		sweeps[b[i][0]].push_back({i, +1});
		sweeps[b[i][1]].push_back({i, -1});
	}
	atcoder::lazy_segtree<node, TT, ET, int, UT, UU, EU> seg(n);
	for (int i = 0; i < n; i++)
		seg.set(i, node(a[i]));
	for (auto &x : b) {
		seg.apply(x[0], x[1], +1);
	}
	lint ans = 0;
	for (int i = 0; i < n; i++) {
		for (auto &[idx, mode] : sweeps[i]) {
			if (mode == -1) {
				seg.apply(b[idx][0], b[idx][1], +1);
				seg.apply(0, b[idx][0], -1);
				seg.apply(b[idx][1], n, -1);
			} else {
				seg.apply(b[idx][0], b[idx][1], -1);
				seg.apply(0, b[idx][0], +1);
				seg.apply(b[idx][1], n, +1);
			}
		}
		auto prd = seg.all_prod();
		if (prd.minv == 0)
			ans = max(ans, prd.mincnt);
	}
	return accumulate(all(a), 0ll) - ans;
}

vector<vector<pi>> gph;
int deg[MAXN], rt[MAXN], dep[MAXN];
int par[20][MAXN], pae[MAXN], r, vis[MAXN];

void dfs(int x, int p) {
	if (deg[x])
		rt[x] = x;
	else
		rt[x] = rt[p];
	vis[x] = 1;
	for (auto &[w, y] : gph[x]) {
		if (vis[y])
			continue;
		par[0][y] = x;
		pae[y] = w;
		dep[y] = dep[x] + 1;
		dfs(y, x);
	}
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
	for (int i = 19; i >= 0; i--) {
		if (par[i][u] != par[i][v]) {
			u = par[i][u];
			v = par[i][v];
		}
	}
	return par[0][u];
}

int pa[MAXN];
lint sums;

int paint(int u, int t) {
	if (u != pa[u])
		return pa[u] = paint(pa[u], t);
	if (dep[u] <= dep[t])
		return u;
	sums += pae[u];
	return pa[u] = paint(par[0][u], t);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	cr(gph, n);
	for (int i = 0; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({w, v});
		gph[v].push_back({w, u});
	}
	queue<int> que;
	for (int i = 0; i < n; i++) {
		deg[i] = sz(gph[i]);
		if (deg[i] == 1) {
			que.push(i);
		}
		pa[i] = i;
	}
	while (sz(que)) {
		int f = que.front();
		que.pop();
		for (auto &[w, y] : gph[f]) {
			if (deg[y]) {
				deg[y]--;
				deg[f]--;
				if (deg[y] == 1)
					que.push(y);
			}
		}
	}
	while (deg[r] != 2)
		r++;
	dfs(r, -1);
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	int seglen = count(deg, deg + n, 2);
	vector<pi> seg;

	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (rt[u] == rt[v]) {
			int l = lca(u, v);
			paint(u, l);
			paint(v, l);
		} else {
			if (dep[rt[u]] > dep[rt[v]])
				swap(u, v);
			paint(u, rt[u]);
			paint(v, rt[v]);
			seg.push_back({dep[rt[u]], dep[rt[v]]});
		}
	}
	vector<lint> vlens(seglen);
	for (int i = 0; i < n; i++) {
		if (i != r && deg[i] == 2) {
			vlens[dep[i] - 1] = pae[i];
		}
		if (i == r) {
			for (auto &[w, j] : gph[i]) {
				if (dep[j] > 1 && deg[j] == 2) {
					vlens.back() = w;
				}
			}
		}
	}
	cout << sums + solve(vlens, seg) << "\n";
}