#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int mod = 998244353;

// Compute a chromatic polynomial of a given graph in O(2^n * n^2) time.
// Credit: nachia @ https://judge.yosupo.jp/submission/217250

template <class E> vector<E> SpsPowerProjection(int n, const vector<E> &A, const vector<E> &W, int m, bool exponential = false) {
	const E a0 = A[0];

	using iter = typename vector<E>::iterator;
	struct {
		vector<int> Chi;
		void init(int n) {
			Chi.resize(1 << n);
			for (int i = 1; i < (1 << n); i++)
				Chi[i] = Chi[i - (i & -i)] + 1;
		}
		void zeta(int n, typename vector<E>::const_iterator a, iter r) {
			int N = n + 1;
			auto z = E(0);
			for (int i = 0; i < N << n; i++)
				r[i] = z;
			for (int i = 0; i < 1 << n; i++)
				r[Chi[i] + i * N] = a[i];
			for (int w = 1; w <= 1 << n; w++)
				for (int d = 0; !(w & (1 << d)); d++) {
					int W = N * (w - (1 << d)), dd = N << d;
					for (int i = N * (w - (2 << d)); i < W; i++)
						r[i + dd] += r[i];
				}
		}
		void comp(int n, iter a, iter r) {
			for (int i = 0; i < (1 << n); i++) {
				copy(a, a + n, r);
				a += (n + 1);
				r += n;
			}
		}
		void conv(int n, iter a, iter b) {
			int N = n + 1;
			for (int i = 0; i < (1 << n); i++) {
				int I = i * N;
				vector<E> Q(N);
				for (int ja = 0; ja <= Chi[i]; ja++)
					for (int jb = Chi[i] - ja, x = min(n - ja, Chi[i]); jb <= x; jb++) {
						Q[ja + jb] += a[ja + I] * b[jb + I];
					}
				copy(Q.begin(), Q.end(), a + I);
			}
		}
		void mobius(int n, iter a, iter r) {
			int N = n + 1;
			for (int w = 1; w <= (1 << n); w++)
				for (int d = 0; !(w & (1 << d)); d++) {
					int W = N * (w - (1 << d)), dd = N << d;
					for (int i = N * (w - (2 << d)); i < W; i++)
						a[i + dd] -= a[i];
				}
			for (int i = 0; i < (1 << n); i++)
				r[i] = a[Chi[i] + i * N];
		}
	} rz;
	rz.init(n);

	vector<vector<E>> zet(n);
	for (int d = 0; d < n; d++)
		zet[d].resize((d + 1) << d);
	for (int i = 0; i < n; i++)
		rz.zeta(i, A.begin() + (1 << i), zet[i].begin());

	vector<E> res(1 << n);
	vector<E> zet2(n << (n - 1));
	vector<E> p(n + 1);
	for (int i = 0; i < (1 << n); i++)
		res[i] = W[i];

	for (int d = n - 1; d >= 0; d--) {
		p[n - 1 - d] = res[0];
		vector<E> buf(1 << d);
		vector<E> buf2(1 << d);
		for (int e = d; e >= 0; e--) {
			reverse(res.begin() + (1 << e), res.begin() + (2 << e));
			rz.zeta(e, res.begin() + (1 << e), zet2.begin());
			rz.conv(e, zet2.begin(), zet[e].begin());
			rz.mobius(e, zet2.begin(), buf2.begin());
			reverse(buf2.begin(), buf2.begin() + (1 << e));
			for (int i = 0; i < (1 << e); i++)
				buf[i] += buf2[i];
		}
		swap(res, buf);
	}
	p[n] = res[0];
	if (!exponential) {
		E f = E(1);
		for (int i = 1; i <= n; i++)
			p[i] *= (f *= E(i));
	}

	if (a0.val != 0) {
		vector<E> comb(n + 1, E(1));
		vector<E> ans(m);
		E c = 1;
		for (int d = 0; d < m; d++) {
			for (int i = 0; i <= n && i + d < m; i++)
				ans[i + d] += comb[i] * c * p[i];
			for (int i = 0; i < n; i++)
				comb[i + 1] += comb[i];
			c *= a0;
		}
		return ans;
	}
	p.resize(m);
	return p;
}

template <class T> vector<T> SetCoverPolynomial(int n, const vector<T> &table) {
	assert(int(table.size()) >= (1 << n));
	int nn = 1 << (n - 1);
	auto table2 = vector<T>(table.begin(), table.begin() + nn);
	table2[0] -= T(1);
	vector<T> weight(nn, 0);
	for (int i = 0; i < nn; i++)
		weight[nn - 1 - i] = table[nn + i];
	auto powerproj = SpsPowerProjection(n - 1, table2, weight, n, true);
	powerproj.insert(powerproj.begin(), T(0));
	vector<T> prod(n + 2);
	vector<T> res(n + 1);
	prod[0] = 1;
	for (int i = 0; i <= n; i++) {
		T I = T(i);
		for (int j = 0; j <= i; j++) {
			res[j] += prod[j] * powerproj[i];
		}
		for (int j = i; j >= 0; j--) {
			prod[j + 1] += prod[j];
			prod[j] *= -I;
		}
	}
	return res;
}

template <class T> vector<T> ChromaticPolynomial(vector<vector<int>> adjacency_matrix) {
	int n = adjacency_matrix.size();
	int nn = 1 << n;
	vector<T> en(nn, 1);
	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++) {
			if (adjacency_matrix[u][v])
				en[(1 << u) | (1 << v)] = 0;
		}
	for (int d = 0; d < n; d++)
		for (int i = 0; i < nn; i++)
			if (i & (1 << d))
				en[i] *= en[i - (1 << d)];
	return SetCoverPolynomial(n, move(en));
}

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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>(n));
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u][v] = adj[v][u] = 1;
	}
	auto g = ChromaticPolynomial<mint>(adj);
	mint ans = 0;
	for (int i = 0; i <= n; i++)
		ans += (i % 2 ? -g[i] : g[i]);
	ans *= mint(m) / mint(2);
	if (n % 2 == 1)
		ans = -ans;
	cout << ans << "\n";
}