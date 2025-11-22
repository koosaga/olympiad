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
	int cnt;
	lint sum[2];
	node() { sum[0] = sum[1] = cnt = 0; }
	node(int x) {
		cnt = 1;
		sum[1] = 0;
		sum[0] = x;
	}
	node operator+(const node &nd) {
		node ret;
		ret.cnt = cnt + nd.cnt;
		ret.sum[0] = sum[0] + nd.sum[cnt % 2];
		ret.sum[1] = sum[1] + nd.sum[(1 + cnt) % 2];
		return ret;
	}
};

node TT(node a, node b) { return a + b; }
node UT(bool a, node b) { return b; }
bool UU(bool a, bool b) { return 0; }
node ET() { return node(); }
bool EU() { return 0; }
int PRED;

bool pred(node v) { return v.cnt <= PRED; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		a[i][1] = i;
	}
	auto b = a;
	sort(all(b));
	vector<array<int, 6>> queries(q);
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < 5; j++)
			cin >> queries[i][j];
		queries[i][0]--;
		queries[i][2] = lower_bound(all(b), pi{queries[i][2], -1}) - b.begin();
		queries[i][3] = lower_bound(all(b), pi{queries[i][3] + 1, -1}) - b.begin();
		queries[i][5] = i;
	}
	vector<int> pos(n);
	for (int i = 0; i < n; i++) {
		pos[i] = lower_bound(all(b), a[i]) - b.begin();
	}
	sort(all(queries), [&](array<int, 6> &a, array<int, 6> &b) {
		if ((a[0] >> 8) != (b[0] >> 8))
			return a[0] < b[0];
		if ((a[0] >> 8) & 1)
			return a[1] > b[1];
		return a[1] < b[1];
	});
	atcoder::lazy_segtree<node, TT, ET, bool, UT, UU, EU> seg(n);
	auto upd = [&](int idx, int d) {
		if (d == -1)
			seg.set(pos[idx], node());
		else
			seg.set(pos[idx], node(b[pos[idx]][0]));
	};
	vector<lint> ans(q);
	int s = 0, e = 0;
	for (auto &x : queries) {
		while (s > x[0])
			upd(--s, +1);
		while (e < x[1])
			upd(e++, +1);
		while (s < x[0])
			upd(s++, -1);
		while (e > x[1])
			upd(--e, -1);
		auto gs = seg.prod(x[2], x[3]);
		int n = min(x[4], gs.cnt);
		if (n == 0)
			continue;
		auto kth = [&](int p) {
			if (p == n)
				return x[3];
			PRED = p;
			return seg.max_right<pred>(x[2]);
		};
		if (n <= 2) {
			ans[x[5]] = b[kth(n - 1)][0];
			continue;
		}
		x[3] = kth(n - 1) + 1;
		lint v0 = b[kth(0)][0];
		lint v1 = b[kth(1)][0];
		int gp1 = lower_bound(all(b), pi{2 * v1 - v0, int(1e9)}) - b.begin();
		gp1 = min(gp1, x[3]);
		int m = seg.prod(x[2], gp1).cnt - 1;
		int k = (n - m - 1) / 2;
		lint ret = v0 * (n - k - 2) + (2 * k + 1) * v1;
		if (2 <= n - k * 2) {
			auto gg = seg.prod(kth(2), kth(n - k * 2));
			ret += gg.sum[0] + gg.sum[1];
		}
		ret += seg.prod(kth(n - k * 2), x[3]).sum[1];
		ans[x[5]] = ret;
	}
	for (auto &x : ans)
		cout << x << "\n";
}