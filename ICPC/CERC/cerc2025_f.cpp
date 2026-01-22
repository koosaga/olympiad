// atcoder lazy segtree.
// aggregation follows aeren treap standard, no monoid trash here
// Source: https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html
// Code below implements https://www.acmicpc.net/problem/33620

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
	int lmax, rmax, opt;
	node() { lmax = rmax = opt = 0; }
	node(int u, int v) { lmax = u, rmax = v, opt = max(u, v); }
	node operator+(const node &nd) const {
		node ret;
		ret.lmax = max(lmax, nd.lmax);
		ret.rmax = max(rmax, nd.rmax);
		ret.opt = max({opt, nd.opt, lmax + nd.rmax});
		return ret;
	}
};

node TT(node a, node b) { return a + b; }
node UT(int a, node b) { return b; }
int UU(int a, int b) { return a + b; }
node ET() { return node(); }
int EU() { return 0; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q, m = 1000005;
	cin >> n >> q;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	int p = 0;
	vector<int> L(n), R(n);
	atcoder::lazy_segtree<node, TT, ET, int, UT, UU, EU> S(m);
	vector<vector<int>> QL(m), QR(m);
	auto go = [&](int v) { S.set(v, node(sz(QL[v]) ? QL[v].back() : 0, sz(QR[v]) ? QR[v].back() : 0)); };
	for (int i = n - 1; i >= p; i--) {
		R[i] = S.prod(a[i] + 1, m).rmax + 1;
		QR[a[i]].push_back(R[i]);
		go(a[i]);
	}
	while (q--) {
		string s;
		cin >> s;
		if (s == "<") {
			p--;
			R[p] = S.prod(a[p] + 1, m).rmax + 1;
			QR[a[p]].push_back(R[p]);
			QL[a[p]].pop_back();
			go(a[p]);
		} else if (s == ">") {
			L[p] = S.prod(0, a[p]).lmax + 1;
			QL[a[p]].push_back(L[p]);
			QR[a[p]].pop_back();
			go(a[p]);
			p++;
		} else {
			int v;
			cin >> v;
			QR[a[p]].pop_back();
			go(a[p]);
			a[p] = v;
			R[p] = S.prod(a[p] + 1, m).rmax + 1;
			QR[a[p]].push_back(R[p]);
			go(a[p]);
			cout << S.all_prod().opt << "\n";
		}
	}
}