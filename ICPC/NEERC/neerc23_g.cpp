#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int mod = 998244353;

struct mint {
	int val;
	mint() { val = 0; }
	mint(const lint &v) {
		val = (-mod <= v && v < mod) ? v : v % mod;
		if (val < 0)
			val += mod;
	}

	friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
	friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint &operator+=(const mint &m) {
		if ((val += m.val) >= mod)
			val -= mod;
		return *this;
	}
	mint &operator-=(const mint &m) {
		if ((val -= m.val) < 0)
			val += mod;
		return *this;
	}
	mint &operator*=(const mint &m) {
		val = (lint)val * m.val % mod;
		return *this;
	}
	friend mint ipow(mint a, lint p) {
		mint ans = 1;
		for (; p; p /= 2, a *= a)
			if (p & 1)
				ans *= a;
		return ans;
	}
	mint inv() const { return ipow(*this, mod - 2); }
	mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

const int MAXT = 530000;
struct seg {
	int tree[MAXT], lazy[MAXT];
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			tree[i] += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void init(int s, int e, int p, vector<lint> &v) {
		if (s == e) {
			tree[p] = v[s];
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2 * p, v);
		init(m + 1, e, 2 * p + 1, v);
		tree[p] = max(tree[2 * p], tree[2 * p + 1]);
	}
	int query(int s, int e, int ps, int pe, int p) {
		if (e < ps || pe < s)
			return -1;
		if (s <= ps && pe <= e)
			return tree[p];
		lazydown(p);
		int pm = (ps + pe) / 2;
		return max(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
	}
	void add(int s, int e, int ps, int pe, int p) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p]++;
			lazy[p]++;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2 * p);
		add(s, e, pm + 1, pe, 2 * p + 1);
		tree[p] = max(tree[2 * p], tree[2 * p + 1]);
	}
	int fuck1(int s, int e, int p) {
		while (s != e) {
			lazydown(p);
			int m = (s + e) / 2;
			if (tree[2 * p] == tree[p]) {
				p = 2 * p;
				e = m;
			} else {
				p = 2 * p + 1;
				s = m + 1;
			}
		}
		return s;
	}
	int fuck2(int s, int e, int p) {
		while (s != e) {
			lazydown(p);
			int m = (s + e) / 2;
			if (tree[2 * p + 1] == tree[p]) {
				p = 2 * p + 1;
				s = m + 1;
			} else {
				p = 2 * p;
				e = m;
			}
		}
		return s;
	}
	pi max_range(int s, int e, int p = 1) {
		if (s == e)
			return pi{s, s};
		int m = (s + e) / 2;
		lazydown(p);
		if (tree[2 * p] == tree[p] && tree[2 * p + 1] == tree[p]) {
			return pi{fuck1(s, m, 2 * p), fuck2(m + 1, e, 2 * p + 1)};
		}
		if (tree[2 * p] == tree[p])
			return max_range(s, m, 2 * p);
		return max_range(m + 1, e, 2 * p + 1);
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<lint> a(n + 2);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	seg.init(0, n + 1, 1, a);
	pi cur = seg.max_range(0, n + 1);
	lint ans = 0, pfx = 0, sfx = 0;
	for (int i = 1; i < cur[0]; i++) {
		pfx = max(pfx, a[i]);
		ans += pfx - a[i];
	}
	for (int i = cur[0]; i <= cur[1]; i++) {
		ans += a[cur[0]] - a[i];
	}
	for (int i = n; i > cur[1]; i--) {
		sfx = max(sfx, a[i]);
		ans += sfx - a[i];
	}
	cout << ans << "\n";
	while (q--) {
		int l, r;
		cin >> l >> r;
		int s = l, e = r;
		ans -= (r - l + 1);
		int leftMax = seg.query(0, l - 1, 0, n + 1, 1);
		int segMax = seg.query(l, r, 0, n + 1, 1);
		int rightMax = seg.query(r + 1, n + 1, 0, n + 1, 1);
		auto getPrefRange = [&]() {
			if (segMax < leftMax)
				return pi{0, -1};
			pi ans;
			{

				int s = l, e = n;
				while (s != e) {
					int m = (s + e) / 2;
					if (seg.query(l, m, 0, n + 1, 1) < leftMax)
						s = m + 1;
					else
						e = m;
				}
				ans[0] = s;
			}
			{
				int s = l, e = n + 1;
				while (s != e) {
					int m = (s + e) / 2;
					if (seg.query(l, m, 0, n + 1, 1) < segMax + 1)
						s = m + 1;
					else
						e = m;
				}
				ans[1] = s - 1;
			}
			return ans;
		};
		auto getSuffRange = [&]() {
			if (segMax < rightMax)
				return pi{0, -1};
			pi ans;
			{

				int s = 1, e = r;
				while (s != e) {
					int m = (s + e) / 2;
					if (seg.query(m + 1, r, 0, n + 1, 1) < rightMax)
						e = m;
					else
						s = m + 1;
				}
				ans[1] = s;
			}
			{
				int s = 0, e = r;
				while (s != e) {
					int m = (s + e) / 2;
					if (seg.query(m + 1, r, 0, n + 1, 1) < segMax + 1)
						e = m;
					else
						s = m + 1;
				}
				ans[0] = s + 1;
			}
			return ans;
		};
		auto [s1, e1] = getPrefRange();
		auto [s2, e2] = getSuffRange();
		auto [s3, e3] = seg.max_range(0, n + 1);
		e1++;
		e2++;
		e3++;
		//	cout << s1 << "," << e1 << " " << s2 << "," << e2 << " " << s3 << "," << e3 << endl;
		ans += max(min(e1, s3) - s1, 0) + max(e2 - max(s2, e3), 0) + max(min({e1, e2, e3}) - max({s1, s2, s3}), 0);
		cout << ans << "\n";
		seg.add(s, e, 0, n + 1, 1);
	}
}
