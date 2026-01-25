#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 250005;
const int MAXT = 530000;

struct bit {
	int tree[MAXT];
	void add(int x, int v) {
		for (int i = x; i < MAXT; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;
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

int threshold;

int TT(int x, int y) { return min(x, y); }
int UT(int a, int b) { return b; }
int UU(int a, int b) { return a + b; }
int ET() { return 1e9; }
int EU() { return 0; }
bool pred(int x) { return x >= threshold; }

struct disj {
	int pa[MAXN], sz[MAXN];
	void init(int n) {
		iota(pa, pa + n, 0);
		fill(sz, sz + n, 1);
	}
	int find(int x) { return pa[x] == x ? x : find(pa[x]); }
	bool uni(int p, int q, vector<pair<int *, int>> &logs) {
		p = find(p);
		q = find(q);
		if (p == q)
			return false;
		if (sz[p] > sz[q])
			swap(p, q);
		logs.push_back({&pa[p], pa[p]});
		pa[p] = q;
		logs.push_back({&sz[q], sz[q]});
		sz[q] += sz[p];
		return true;
	}

	int getsz(int x) { return sz[find(x)]; }

	void rollback(vector<pair<int *, int>> &logs) {
		while (sz(logs)) {
			auto [addr, val] = logs.back();
			logs.pop_back();
			*addr = val;
		}
	}
} disj;

vector<pi> edges[MAXT];
vector<int> active[MAXT];
vector<pi> mapping[MAXT];

// ids : takes id -> return priority
// sfx_arr : takes rank -> return (some)id
// rev_sfx : takes id -> return (tie not broken)rank
vector<int> sfx_arr[MAXT], rev_sfx[MAXT];
vector<pi> ids[MAXT];

vector<int> pfx_arr[MAXT], rev_pfx[MAXT];
vector<pi> idp[MAXT];

vector<int> ans;

// takes id -> return lcs
int get_lcs(int s, int e, int p, int u, int v) {
	if (s == e) {
		return u == v;
	}
	int m = (s + e) / 2;
	if (idp[p][u][0] != idp[p][v][0]) {
		if (idp[p][u][0] >= MAXT || idp[p][v][0] >= MAXT)
			return 0;
		return get_lcs(m + 1, e, 2 * p + 1, pfx_arr[2 * p + 1][idp[p][u][0]], pfx_arr[2 * p + 1][idp[p][v][0]]);
	}
	if (idp[p][u][1] != idp[p][v][1]) {
		if (idp[p][u][1] >= MAXT || idp[p][v][1] >= MAXT)
			return e - m;
		return e - m + get_lcs(s, m, 2 * p, pfx_arr[2 * p][idp[p][u][1]], pfx_arr[2 * p][idp[p][v][1]]);
	}
	return e - s + 1;
}

int get_lcp(int s, int e, int p, int u, int v) {
	if (s == e) {
		return u == v;
	}
	int m = (s + e) / 2;
	if (ids[p][u][0] != ids[p][v][0]) {
		if (ids[p][u][0] >= MAXT || ids[p][v][0] >= MAXT)
			return 0;
		return get_lcp(s, m, 2 * p, sfx_arr[2 * p][ids[p][u][0]], sfx_arr[2 * p][ids[p][v][0]]);
	}
	if (ids[p][u][1] != ids[p][v][1]) {
		if (ids[p][u][1] >= MAXT || ids[p][v][1] >= MAXT)
			return m - s + 1;
		return m - s + 1 +
			   get_lcp(m + 1, e, 2 * p + 1, sfx_arr[2 * p + 1][ids[p][u][1]], sfx_arr[2 * p + 1][ids[p][v][1]]);
	}
	return e - s + 1;
}

pair<vector<int>, vector<int>> GEN(vector<pi> &src) {
	vector<int> sfx(sz(src)), rev(sz(src));
	iota(all(sfx), 0);
	sort(all(sfx), [&](const int &a, const int &b) { return src[a] < src[b]; });
	int c = 0;
	vector<int> trace = {sfx[0]};
	for (int i = 0; i < sz(src); i++) {
		rev[sfx[i]] = c;
		if (i + 1 < sz(src) && src[sfx[i]] != src[sfx[i + 1]]) {
			trace.push_back(sfx[i + 1]);
			c++;
		}
	}
	for (int i = 0; i < sz(sfx); i++) {
		assert(src[trace[rev[i]]] == src[i]);
	}
	return make_pair(trace, rev);
}

void solve(int s, int e, int p, vector<array<int, 4>> &queries) {
	vector<pair<int *, int>> rback;
	for (auto &[l, r] : edges[p]) {
		disj.uni(l, r, rback);
	}

	// pruning non interesting queries
	for (auto &v : active[p]) {
		mapping[p].push_back({v, disj.find(v)});
		v = disj.find(v);
	}
	sort(all(active[p]));
	active[p].resize(unique(all(active[p])) - active[p].begin());
	if (p > 1) {
		for (auto &v : active[p / 2]) {
			if (binary_search(all(active[p]), disj.find(v)))
				mapping[p].push_back({v, disj.find(v)});
		}
	}

	for (auto &z : mapping[p]) {
		z[1] = lower_bound(all(active[p]), z[1]) - active[p].begin();
	}
	sort(all(mapping[p]));
	mapping[p].resize(unique(all(mapping[p])) - mapping[p].begin());

	vector<array<int, 4>> todo;
	for (auto &[l, r, z, i] : queries) {
		z = disj.find(z);
		if (!binary_search(all(active[p]), z)) {
			ans[i] = disj.getsz(z);
		} else
			todo.push_back({l, r, z, i});
	}
	queries = todo;

	if (s == e) {
		sfx_arr[p].resize(sz(active[p]));
		iota(all(sfx_arr[p]), 0);
		rev_sfx[p] = sfx_arr[p];

		pfx_arr[p] = sfx_arr[p];
		rev_pfx[p] = rev_sfx[p];
		for (auto &[l, r, z, i] : queries) {
			assert(l == s && r == e + 1);
			ans[i] = disj.getsz(z);
		}
	} else {
		int m = (s + e) / 2;
		vector<array<int, 4>> sub[2], M;
		for (auto &[l, r, z, i] : queries) {
			if (r <= m + 1)
				sub[0].push_back({l, r, z, i});
			else if (l >= m + 1)
				sub[1].push_back({l, r, z, i});
			else
				M.push_back({l, r, z, i});
		}

		solve(s, m, 2 * p, sub[0]);
		solve(m + 1, e, 2 * p + 1, sub[1]);

		// mapping: takes absolute vertex no -> return id
		auto locate = [&](int ch, int v) {
			int it = lower_bound(all(mapping[2 * p + ch]), pi{v, -1}) - mapping[2 * p + ch].begin();
			if (it != sz(mapping[2 * p + ch]) && mapping[2 * p + ch][it][0] == v) {
				return mapping[2 * p + ch][it][1];
			}
			return -1;
		};

		cr(ids[p], sz(active[p]));
		for (int ch = 0; ch < 2; ch++) {
			for (int i = 0; i < sz(active[p]); i++) {
				int j = locate(ch, active[p][i]);
				if (j == -1)
					ids[p][i][ch] = MAXT + active[p][i];
				else
					ids[p][i][ch] = rev_sfx[2 * p + ch][j];
			}
		}
		tie(sfx_arr[p], rev_sfx[p]) = GEN(ids[p]);

		cr(idp[p], sz(active[p]));
		for (int ch = 0; ch < 2; ch++) {
			for (int i = 0; i < sz(active[p]); i++) {
				int j = locate(1 - ch, active[p][i]);
				if (j == -1)
					idp[p][i][ch] = MAXT + active[p][i];
				else
					idp[p][i][ch] = rev_pfx[2 * p + 1 - ch][j];
			}
		}
		tie(pfx_arr[p], rev_pfx[p]) = GEN(idp[p]);

		if (sz(M)) {
			vector<pi> idxL, idxR;
			for (int i = 0; i < sz(active[p]); i++) {
				auto prodL = pi{idp[p][i][1], i};
				auto prodR = pi{ids[p][i][1], i};
				idxL.push_back(prodL);
				idxR.push_back(prodR);
			}
			sort(all(idxL));
			sort(all(idxR));

			vector<int> revL(sz(active[p])), lcpL(sz(active[p]) - 1);
			vector<int> revR(sz(active[p])), lcpR(sz(active[p]) - 1);
			for (int i = 0; i < sz(active[p]); i++) {
				revL[idxL[i][1]] = i;
				revR[idxR[i][1]] = i;
			}
			auto get_lcs_wrap = [&](pi x, pi y) {
				if (x[0] >= MAXT || y[0] >= MAXT) {
					return x[0] == y[0] ? (m + 1 - s) : 0;
				}
				return get_lcs(s, m, 2 * p, pfx_arr[2 * p][x[0]], pfx_arr[2 * p][y[0]]);
			};
			auto get_lcp_wrap = [&](pi x, pi y) {
				if (x[0] >= MAXT || y[0] >= MAXT) {
					return x[0] == y[0] ? (e - m) : 0;
				}
				return get_lcp(m + 1, e, 2 * p + 1, sfx_arr[2 * p + 1][x[0]], sfx_arr[2 * p + 1][y[0]]);
			};
			for (int i = 0; i < sz(active[p]) - 1; i++) {
				lcpL[i] = get_lcs_wrap(idxL[i], idxL[i + 1]);
				lcpR[i] = get_lcp_wrap(idxR[i], idxR[i + 1]);
			}
			atcoder::lazy_segtree<int, TT, ET, int, UT, UU, EU> lseg(lcpL), rseg(lcpR);
			vector<pi> points(sz(active[p]));
			vector<vector<array<int, 4>>> queries(sz(active[p]));
			for (int x = 0; x < sz(active[p]); x++) {
				points[revL[x]] = {revR[x], disj.getsz(active[p][x])};
			}
			for (auto &[l, r, z, i] : M) {
				int pos = lower_bound(all(active[p]), z) - active[p].begin();
				threshold = m + 1 - l;
				int l1 = lseg.min_left<pred>(revL[pos]);
				int r1 = lseg.max_right<pred>(revL[pos]);
				threshold = r - m - 1;
				int l2 = rseg.min_left<pred>(revR[pos]);
				int r2 = rseg.max_right<pred>(revR[pos]);
				queries[r1].push_back({l2, r2, +1, i});
				if (l1 > 0)
					queries[l1 - 1].push_back({l2, r2, -1, i});
			}
			for (int i = 0; i < sz(active[p]); i++) {
				bit.add(points[i][0] + 1, points[i][1]);
				for (auto &[l, r, d, p] : queries[i]) {
					ans[p] += d * (bit.query(r + 1) - bit.query(l));
				}
			}
			for (int i = 0; i < sz(active[p]); i++)
				bit.add(points[i][0] + 1, -points[i][1]);
		}
	}
	disj.rollback(rback);
}

void add_edge(int s, int e, int ps, int pe, int p, pi v) {
	if (e < ps || pe < s)
		return;
	active[p].push_back(v[0]);
	active[p].push_back(v[1]);
	if (s <= ps && pe <= e) {
		edges[p].push_back(v);
		return;
	}
	int pm = (ps + pe) / 2;
	add_edge(s, e, ps, pm, 2 * p, v);
	add_edge(s, e, pm + 1, pe, 2 * p + 1, v);
}

vector<int> count_computers(int N, int T, int Q, vector<vector<array<int, 2>>> E, vector<array<int, 3>> F) {
	disj.init(N);
	map<pi, int> edges;
	auto add_interval = [&](int l, int r, pi edges) { add_edge(l, r, 0, T, 1, edges); };
	for (int i = 1; i <= T; i++) {
		for (auto &[u, v] : E[i - 1]) {
			if (edges.count(pi{u, v})) {
				add_interval(edges[pi{u, v}], i - 1, pi{u, v});
				edges.erase(pi{u, v});
			} else
				edges[pi{u, v}] = i;
		}
	}
	for (auto &[e, t] : edges)
		add_interval(t, T, e);
	vector<array<int, 4>> queries;
	for (int i = 0; i < Q; i++) {
		auto [v, l, r] = F[i];
		queries.push_back({l, r + 1, v, i});
	}
	cr(ans, Q);
	solve(0, T, 1, queries);
	return ans;
}
