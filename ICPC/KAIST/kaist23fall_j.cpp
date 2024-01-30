#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using llf = long double;
// source: https://github.com/justiceHui/icpc-teamnote/blob/master/code/Math/Matrix.cpp

const int mod = 998244353; // 1e9 + 7;//993244853;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.

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

template <typename T> bool IsZero(T x) { return x == mint(0); }
template <typename T> T Add(T a, T b) { return a + b; }
template <typename T> T Sub(T a, T b) { return a - b; }
template <typename T> T Mul(T a, T b) { return a * b; }
template <typename T> T Div(T a, T b) { return a / b; }

template <typename T, bool calc_inv> // return {rref, rank, det, inv}
tuple<vector<vector<T>>, int, T, vector<vector<T>>> Gauss(vector<vector<T>> a) {
	int n = a.size(), m = a[0].size(), rank = 0;
	assert(n == m || !calc_inv);
	vector<vector<T>> out(n, vector<T>(m, 0));
	T det = T(1);
	if constexpr (calc_inv)
		for (int i = 0; i < n; i++)
			out[i][i] = T(1);
	for (int i = 0; i < m; i++) {
		if (rank == n)
			break;
		if (IsZero(a[rank][i])) {
			T mx = T(0);
			int idx = -1; // fucking precision error
			for (int j = rank + 1; j < n; j++) {
				if (a[j][i].val != 0)
					idx = j;
			}
			if (idx == -1 || IsZero(a[idx][i])) {
				det = 0;
				continue;
			}
			for (int k = 0; k < m; k++) {
				a[rank][k] = Add(a[rank][k], a[idx][k]);
				if constexpr (calc_inv)
					out[rank][k] = Add(out[rank][k], out[idx][k]);
			}
		}
		det = Mul(det, a[rank][i]);
		T coeff = Div(T(1), a[rank][i]);
		for (int j = 0; j < m; j++)
			a[rank][j] = Mul(a[rank][j], coeff);
		if constexpr (calc_inv)
			for (int j = 0; j < m; j++)
				out[rank][j] = Mul(out[rank][j], coeff);
		for (int j = 0; j < n; j++) {
			if (rank == j)
				continue;
			T t = a[j][i]; // Warning: [j][k], [rank][k]
			for (int k = 0; k < m; k++)
				a[j][k] = Sub(a[j][k], Mul(a[rank][k], t));
			if constexpr (calc_inv)
				for (int k = 0; k < m; k++)
					out[j][k] = Sub(out[j][k], Mul(out[rank][k], t));
		}
		rank++; // linear system: warning len(A) != len(A[0])
	}
	return {a, rank, det, out}; // linear system: get RREF(A|b)
} // 0 0 ... 0 b[i]: inconsistent, rank < len(A[0]): multiple

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<array<int, 4>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1] >> a[i][2];
		a[i][3] = i;
	}
	lint ans = 1e18;
	if (a[0][2] == a[n - 1][2])
		ans = max(abs(a[0][1] - a[n - 1][1]), abs(a[0][0] - a[n - 1][0]));
	vector<vector<pi>> gph(3 * n);
	auto addEdge = [&](int s, int e, int x) { gph[s].push_back({x, e}); };
	for (int d = 0; d < 2; d++) {
		sort(all(a), [&](const array<int, 4> &p, const array<int, 4> &q) { return p[d] < q[d]; });
		for (int i = 0; i < n;) {
			int j = i;
			while (j < n && a[i][2] == a[j][2])
				j++;
			for (int k = i; k < j; k++) {
				if (i)
					addEdge(a[k][3], a[i - 1][3] + n * (d + 1), a[k][d] - a[i - 1][d]);
				if (j < n)
					addEdge(a[k][3], a[j][3] + n * (d + 1), a[j][d] - a[k][d]);
			}
			i = j;
		}
		sort(all(a), [&](const array<int, 4> &p, const array<int, 4> &q) {
			if (p[2] != q[2])
				return p[2] < q[2];
			return p[d] < q[d];
		});
		for (int i = 0; i < n;) {
			int j = i;
			while (j < n && a[i][2] == a[j][2])
				j++;
			for (int k = i + 1; k < j; k++) {
				addEdge(a[k - 1][3] + n * (d + 1), a[k][3] + n * (d + 1), a[k][d] - a[k - 1][d]);
				addEdge(a[k][3] + n * (d + 1), a[k - 1][3] + n * (d + 1), a[k][d] - a[k - 1][d]);
			}
			i = j;
		}
	}
	for (int i = 0; i < n; i++) {
		addEdge(i + 2 * n, i, 0);
		addEdge(i + n, i, 0);
	}
	vector<lint> dist(3 * n, 1e18);
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	auto enq = [&](lint d, int x) {
		if (dist[x] > d) {
			dist[x] = d;
			pq.push({d, x});
		}
	};
	enq(0, 0);
	while (sz(pq)) {
		auto x = pq.top();
		pq.pop();
		if (dist[x[1]] != x[0])
			continue;
		for (auto &[w, y] : gph[x[1]]) {
			enq(x[0] + w, y);
		}
	}
	cout << min(ans, dist[n - 1]) << "\n";
}