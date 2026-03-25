#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const lint oo = 1e18;

array<lint, 3> comb(pi a, pi b) { return array<lint, 3>{a[0] + b[0], a[1], b[1]}; }
struct node {
	int cost;
	pi maxv[2][2][2];		// (0, 1) * (need min from left if 1) * (right )
	array<lint, 3> sol;		// (01)
	array<lint, 3> skew[2]; // (10 midpassage 0/1)
	node() {
		cost = 1e9;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					maxv[i][j][k] = pi{-oo, -1};
				}
			}
		}
		sol = skew[0] = skew[1] = array<lint, 3>{-oo, -1, -1};
	}
	node(int x) {
		cost = x;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					maxv[i][j][k] = pi{-oo, -1};
				}
			}
		}
		sol = skew[0] = skew[1] = array<lint, 3>{-oo, -1, -1};
	}
	node(char c, int x, int idx) {
		cost = 1e9;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					maxv[i][j][k] = pi{-oo, -1};
				}
			}
		}
		sol = skew[0] = skew[1] = array<lint, 3>{-oo, -1, -1};
		maxv[c == ')'][1][1] = pi{x, idx};
	}
	node operator+(const node &nd) const {
		node ret;
		ret.cost = min(cost, nd.cost);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					ret.maxv[i][j][k] = pi{-oo, -1};
				}
			}
		}
		ret.sol = ret.skew[0] = ret.skew[1] = array<lint, 3>{-oo, -1, -1};
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					if (ret.cost == cost && ret.cost == nd.cost) {
						ret.maxv[i][j][1] = max(ret.maxv[i][j][1], maxv[i][j][k]);
						ret.maxv[i][1][k] = max(ret.maxv[i][1][k], nd.maxv[i][j][k]);
					} else if (ret.cost == cost) {
						ret.maxv[i][j][k] = max(ret.maxv[i][j][k], maxv[i][j][k]);
						ret.maxv[i][1][0] = max(ret.maxv[i][1][0], nd.maxv[i][j][k]);
					} else {
						ret.maxv[i][0][1] = max(ret.maxv[i][0][1], maxv[i][j][k]);
						ret.maxv[i][j][k] = max(ret.maxv[i][j][k], nd.maxv[i][j][k]);
					}
				}
			}
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					if (j)
						ret.maxv[i][j][k] = max(ret.maxv[i][j][k], ret.maxv[i][j - 1][k]);
					if (k)
						ret.maxv[i][j][k] = max(ret.maxv[i][j][k], ret.maxv[i][j][k - 1]);
				}
			}
		}
		ret.sol = max({sol, nd.sol, comb(maxv[0][1][1], nd.maxv[1][1][1])});
		for (int j = 0; j < 2; j++) {
			ret.skew[j & (ret.cost == cost)] = max(ret.skew[j & (ret.cost == cost)], skew[j]);
			ret.skew[j & (ret.cost == nd.cost)] = max(ret.skew[j & (ret.cost == nd.cost)], nd.skew[j]);
		}
		ret.skew[0] = max(ret.skew[0], comb(nd.maxv[0][ret.cost < nd.cost][1], maxv[1][1][ret.cost < cost]));
		ret.skew[1] = max(ret.skew[1], comb(nd.maxv[0][1][1], maxv[1][1][1]));
		ret.skew[1] = max(ret.skew[1], ret.skew[0]);
		return ret;
	}
};

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

node TT(node a, node b) { return a + b; }
node UT(int a, node b) {
	b.cost += a;
	return b;
}

int UU(int a, int b) { return a + b; }
node ET() { return node(); }
int EU() { return 0; }

vector<lint> solve(vector<pi> A, vector<pi> B) {
	// do gwalho dance
	vector<pi> foo;
	for (auto &[x, c] : A) {
		foo.push_back(pi{2 * x, c});
	}
	for (auto &[x, c] : B) {
		foo.push_back(pi{2 * x + 1, c});
	}
	sort(all(foo));
	int n = sz(foo);
	string s;
	vector<lint> a;
	for (int i = 0; i < n; i++) {
		s.push_back("()"[foo[i][0] & 1]);
		a.push_back(-foo[i][1]);
	}

	vector<node> seq;
	for (int i = 0; i < n; i++) {
		seq.push_back(node(s[i], a[i], i));
		seq.push_back(node(0));
	}
	bool fucked = false;
	lint dap = 0;
	vector<lint> ret = {0};
	auto seg = atcoder::lazy_segtree<node, TT, ET, int, UT, UU, EU>(seq);
	for (int k = 1; k <= n / 2; k++) {
		if (fucked) {
			return ret;
		}
		auto ans = seg.all_prod();
		assert(ans.cost == 0);
		array<lint, 3> ope = max(ans.sol, ans.skew[0]);
		if (ope[0] < -1e17) {
			return ret;
		}
		dap += ope[0];
		ret.push_back(-dap);
		seg.set(2 * ope[1], node());
		seg.set(2 * ope[2], node());
		if (ope[1] < ope[2]) {
			seg.apply(2 * ope[1], 2 * ope[2], +1);
		} else {
			seg.apply(2 * ope[2], 2 * ope[1], -1);
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k, n;
	cin >> n >> k;
	vector<pi> pos[4];
	for (int i = 0; i < n; i++) {
		int t;
		pi a;
		int c;
		cin >> t >> a[0] >> a[1] >> c;
		t--;
		pos[t ^ 1].push_back(pi{a[t >> 1], c});
	}
	vector<lint> s1 = solve(pos[0], pos[1]);
	vector<lint> s2 = solve(pos[2], pos[3]);
	lint ans = 1e18;
	for (int i = 0; i <= k; i++) {
		if (i < sz(s1) && k - i < sz(s2))
			ans = min(ans, s1[i] + s2[k - i]);
	}
	if (ans > 1e17)
		ans = -1;
	cout << ans << "\n";
}