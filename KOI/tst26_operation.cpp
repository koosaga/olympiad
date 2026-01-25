#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
// atcoder lazy segtree.
// aggregation follows aeren treap standard, no monoid trash here
// Source: https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html
// Code below implements https://www.acmicpc.net/problem/33620
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
	int minv, agg, aggNot;
	node() { minv = 1e9, agg = 1e9, aggNot = 1e9; }
	node(int v, int x) {
		minv = v;
		agg = x;
		aggNot = 1e9;
	}
	node operator+(const node &nd) {
		node ret;
		ret.minv = min(minv, nd.minv);
		ret.agg = min(agg, nd.agg);
		ret.aggNot = min(aggNot, nd.aggNot);
		if (ret.minv != minv)
			ret.aggNot = min(ret.aggNot, agg);
		if (ret.minv != nd.minv)
			ret.aggNot = min(ret.aggNot, nd.agg);
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

vector<int> dap;

void solve(vector<int> &a, vector<int> &b, int l, int r, vector<array<int, 3>> &q) {
	if (l == r) {
		for (auto &[_, __, idx] : q) {
			dap[idx] = (a[l] == b[l]);
		}
		return;
	}
	int m = (l + r) / 2;
	vector<array<int, 3>> ql, qr, qm;
	for (auto &[s, e, idx] : q) {
		if (e <= m)
			ql.push_back({s, e, idx});
		else if (s > m)
			qr.push_back({s, e, idx});
		else
			qm.push_back({s, e, idx});
	}
	solve(a, b, l, m, ql);
	solve(a, b, m + 1, r, qr);
	vector<int> crd(b.begin() + l, b.begin() + r + 1);
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	vector<pi> intv;
	vector<int> pos;
	for (int j = l; j <= r; j++) {
		int ps = lower_bound(all(crd), a[j]) - crd.begin();
		int pe = lower_bound(all(crd), b[j]) - crd.begin();
		if (pe - ps != b[j] - a[j]) {
			intv.push_back({0, pe + 1});
		} else {
			intv.push_back({ps + 1, pe + 1});
		}
		pos.push_back(pe + 1);
	}
	for (auto &x : qm)
		dap[x[2]] = 1;
	{
		sort(all(qm), [&](const array<int, 3> &a, const array<int, 3> &b) { return a[1] < b[1]; });
		vector<node> nd(sz(crd) + 2, node(0, -int(1e9)));
		for (int i = l; i <= m; i++) {
			nd[pos[i - l]] = node(0, i);
		}
		atcoder::lazy_segtree<node, TT, ET, int, UT, UU, EU> seg(nd);
		int j = 0;
		for (int i = m + 1; i <= r; i++) {
			seg.apply(intv[i - l][0], intv[i - l][1], +1);
			node val = seg.get(pos[i - l]);
			val.agg = i;
			seg.set(pos[i - l], val);
			while (j < sz(qm) && qm[j][1] == i) {
				auto tot = seg.all_prod();
				assert(tot.minv == 0);
				if (tot.aggNot < qm[j][0])
					dap[qm[j][2]] = false;
				j++;
			}
		}
	}
	{
		sort(all(qm), [&](const array<int, 3> &a, const array<int, 3> &b) { return a[0] > b[0]; });
		vector<node> nd(sz(crd) + 2, node(0, -int(1e9)));
		for (int i = r; i >= m + 1; i--) {
			nd[pos[i - l]] = node(0, -i);
		}
		atcoder::lazy_segtree<node, TT, ET, int, UT, UU, EU> seg(nd);
		int j = 0;
		for (int i = m; i >= l; i--) {
			seg.apply(intv[i - l][0], intv[i - l][1], +1);
			node val = seg.get(pos[i - l]);
			val.agg = -i;
			seg.set(pos[i - l], val);
			while (j < sz(qm) && qm[j][0] == i) {
				auto tot = seg.all_prod();
				assert(tot.minv == 0);
				if (tot.aggNot < -qm[j][1])
					dap[qm[j][2]] = false;
				j++;
			}
		}
	}
}

vector<int> array_operation(vector<int> A, vector<int> B, vector<int> L, vector<int> R) {
	int n = sz(A);
	int q = sz(L);
	cr(dap, q);
	vector<array<int, 3>> qlist;
	for (int i = 0; i < q; i++) {
		qlist.push_back({L[i], R[i], i});
	}
	solve(A, B, 0, n - 1, qlist);
	return dap;
}