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
lint TT(lint a, lint b) { return max(a, b); }
lint UT(lint a, lint b) { return a + b; }
lint UU(lint a, lint b) { return a + b; }
lint ET() { return lint(-1e18); }
lint EU() { return 0; }

vector<int> solve(int m, int segsz, lint T, vector<array<lint, 5>> rect) {
	vector<lint> arr(segsz);
	atcoder::lazy_segtree<lint, TT, ET, lint, UT, UU, EU> seg(arr);
	int n = sz(rect);
	int ptr = n;
	vector<vector<array<lint, 5>>> sweeps(m);
	for (int i = 0; i < n; i++) {
		sweeps[rect[i][0]].push_back({rect[i][2], rect[i][3], rect[i][4], i, +1});
		sweeps[rect[i][1]].push_back({rect[i][2], rect[i][3], rect[i][4], i, -1});
	}
	vector<int> ans(n);
	for (int i = 0; i < m; i++) {
		for (auto &[l, r, v, idx, mode] : sweeps[i]) {
			if (idx >= ptr)
				continue;
			seg.apply(l, r, v * mode);
		}
		while (seg.all_prod() >= T) {
			ptr--;

			if (rect[ptr][0] <= i && i < rect[ptr][1]) {
				seg.apply(rect[ptr][2], rect[ptr][3], -rect[ptr][4]);
			}
			ans[ptr] = i;
		}
	}
	while (ptr)
		ans[--ptr] = int(1e9);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint h, w, n, x;
	cin >> h >> w >> n >> x;
	vector<int> vx, vy;
	vector<array<lint, 5>> rects(n);
	for (auto &[sx, ex, sy, ey, c] : rects) {
		cin >> sx >> ex >> sy >> ey >> c;
		sx--;
		sy--;
		vx.push_back(sx);
		vx.push_back(ex);
		vy.push_back(sy);
		vy.push_back(ey);
	}
	sort(all(vx));
	sort(all(vy));
	vx.resize(unique(all(vx)) - vx.begin());
	vy.resize(unique(all(vy)) - vy.begin());
	for (auto &[sx, ex, sy, ey, c] : rects) {
		sx = lower_bound(all(vx), sx) - vx.begin();
		ex = lower_bound(all(vx), ex) - vx.begin();
		sy = lower_bound(all(vy), sy) - vy.begin();
		ey = lower_bound(all(vy), ey) - vy.begin();
	}
	vector<int> s[4];
	for (int it = 0; it < 2; it++) {
		s[2 * it + 0] = solve(sz(vx), sz(vy), x, rects); // min X
		for (auto &[sx, ex, sy, ey, c] : rects) {
			sx = sz(vx) - 1 - sx;
			ex = sz(vx) - 1 - ex;
			swap(sx, ex);
		}
		s[2 * it + 1] = solve(sz(vx), sz(vy), x, rects); // max X
		for (auto &z : s[2 * it + 1])
			z = sz(vx) - 1 - z;
		for (auto &[sx, ex, sy, ey, c] : rects) {
			sx = sz(vx) - 1 - sx;
			ex = sz(vx) - 1 - ex;
			swap(sx, ex);
		}
		for (auto &[sx, ex, sy, ey, c] : rects) {
			swap(sx, sy);
			swap(ex, ey);
		}
		swap(vx, vy);
	}
	for (int i = 0; i < n; i++) {
		if (s[0][i] >= s[1][i] || s[2][i] >= s[3][i])
			cout << "0\n";
		else
			cout << 1ll * (vx[s[1][i]] - vx[s[0][i]]) * (vy[s[3][i]] - vy[s[2][i]]) << "\n";
	}
}