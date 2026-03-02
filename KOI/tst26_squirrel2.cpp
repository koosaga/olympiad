#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

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
	int adj[3][3];
	node() { memset(adj, 0, sizeof(adj)); }
	node(int typ) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i <= typ; i++) {
			for (int j = typ; j < 3; j++)
				adj[i][j] = 1;
		}
	}
	node operator+(const node &nd) {
		node ret;
		for (int i = 0; i < 3; i++) {
			for (int j = i; j < 3; j++) {
				for (int k = j; k < 3; k++) {
					ret.adj[i][k] = max(ret.adj[i][k], adj[i][j] + nd.adj[j][k]);
				}
			}
		}
		return ret;
	}
};

node TT(node a, node b) { return a + b; }
node UT(int a, node b) { return b; }
int UU(int a, int b) { return a + b; }
node ET() { return node(); }
int EU() { return 0; }

pi TT2(pi a, pi b) { return max(a, b); }
pi UT2(int a, pi b) { return b; }
int UU2(int a, int b) { return a + b; }
pi ET2() { return pi{-int(1e9), 0}; }
int EU2() { return 0; }

node lnode, rnode;

bool pred1(node x) {
	int cur_opt = x.adj[0][1] + lnode.adj[0][0] - x.adj[0][0];
	int real_opt = lnode.adj[0][1];
	return cur_opt < real_opt;
}

bool pred2(node x) {
	int cur_opt = x.adj[1][2] + rnode.adj[2][2] - x.adj[2][2];
	int real_opt = rnode.adj[1][2];
	return cur_opt < real_opt;
}

vector<lint> fly(int m, vector<int> A, vector<int> B, vector<int> L, vector<int> R) {
	int n = sz(A);
	L[n - 1] = max(L[n - 1], m);
	R[n - 1] = min(R[n - 1], m);
	L.insert(L.begin(), 0);
	R.insert(R.begin(), 0);
	for (int i = 1; i <= n; i++) {
		L[i] = max(L[i - 1], L[i]);
		R[i] = min(R[i - 1] + 1, R[i]);
	}
	for (int i = n - 1; i >= 0; i--) {
		R[i] = min(R[i + 1], R[i]);
		L[i] = max(L[i + 1] - 1, L[i]);
	}
	for (int i = 0; i <= n; i++) {
		if (L[i] > R[i])
			return vector<lint>(m + 1, -1);
	}
	vector<pi> intvs(m);
	for (int i = 1; i <= n; i++) {
		if (L[i - 1] + 1 == L[i])
			intvs[L[i - 1]][1] = i - 1;
		if (R[i - 1] + 1 == R[i]) {
			intvs[R[i - 1]][0] = i - 1;
		}
	}
	vector<pi> vect;
	for (int i = 0; i < n; i++) {
		vect.push_back({i, 0});
	}
	for (int i = 0; i < m; i++) {
		vect.push_back({intvs[i][0], -1});
		vect.push_back({intvs[i][1], +1});
	}
	sort(all(vect));
	vector<array<lint, 3>> greedy; // (type, cost, idx(tiebreaker also))
	for (int i = 0; i < sz(vect); i++) {
		if (vect[i][1] == 0) {
			greedy.push_back({B[vect[i][0]], A[vect[i][0]], i});
		}
	}
	vector<node> nodes(sz(vect));
	for (int i = 0; i < m; i++) {
		int l = lower_bound(all(vect), pi{intvs[i][0], -1}) - vect.begin();
		int r = lower_bound(all(vect), pi{intvs[i][1], +1}) - vect.begin();
		nodes[l] = node(2);
		nodes[r] = node(0);
	}
	atcoder::lazy_segtree<node, TT, ET, int, UT, UU, EU> seg(nodes);
	atcoder::lazy_segtree<pi, TT2, ET2, int, UT2, UU2, EU2> segmax(sz(vect));
	sort(all(greedy));
	lint ans = 0;
	int tsum = 0;
	vector<pi> backedges;
	for (auto &[type, cost, pos] : greedy) {
		seg.set(pos, node(1));
		if (seg.all_prod().adj[0][2] > m) {
			if (type == 1) {
				backedges.push_back({cost, pos});
			}
			seg.set(pos, node());
		} else {
			{
				if (type == 0) {
					segmax.set(pos, pi{cost, pos});
				}
				tsum += type;
				ans += cost;
			}
		}
	}
	assert(seg.all_prod().adj[0][2] == m);

	vector<lint> alist;
	for (auto &[cost, pos] : backedges) {
		seg.set(pos, node(1));
		lnode = seg.prod(0, pos + 1);
		rnode = seg.prod(pos, sz(vect));
		int lpos = seg.min_left<pred1>(pos + 1) - 1;
		int rpos = seg.max_right<pred2>(pos) + 1;
		assert(lpos <= pos && rpos >= pos + 1);
		auto query = segmax.prod(lpos, rpos);
		if (query[0] < 0) {
			seg.set(pos, node());
			continue;
		}
		seg.set(query[1], node());
		segmax.set(query[1], pi{int(-1e9), 0});
		alist.push_back(cost - query[0]);
	}
	sort(all(alist));
	vector<lint> dap(m + 1, -1);
	dap[tsum] = ans;
	for (int i = 0; i < sz(alist); i++) {
		ans += alist[i];
		dap[tsum + i + 1] = ans;
	}
	return dap;
}