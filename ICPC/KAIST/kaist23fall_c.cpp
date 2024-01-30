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

const int MAXN = 2005;

int nxt[4][MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	int dx[256] = {}, dy[256] = {};
	dx['U'] = -1;
	dx['D'] = +1;
	dy['L'] = -1;
	dy['R'] = +1;
	vector<string> a(n);
	for (auto &x : a)
		cin >> x;
	auto ok = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; };
	vector<vector<int>> vis(n, vector<int>(m));
	queue<pi> que;
	auto enq = [&](int x, int y) {
		if (!vis[x][y]) {
			vis[x][y] = 1;
			que.push({x, y});
		}
	};
	string dirs = "LURD";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!ok(i + dx[a[i][j]] * k, j + dy[a[i][j]] * k)) {
				enq(i, j);
			}
		}
	}
	for (int j = 0; j < n; j++) {
		int prv = -1e9;
		for (int k = 0; k < m; k++) {
			nxt[0][j][k] = prv;
			if (a[j][k] == dirs[2])
				prv = k;
		}
		prv = 1e9;
		for (int k = m - 1; k >= 0; k--) {
			nxt[2][j][k] = prv;
			if (a[j][k] == dirs[0])
				prv = k;
		}
	}
	for (int k = 0; k < m; k++) {
		int prv = -1e9;
		for (int j = 0; j < n; j++) {
			nxt[1][j][k] = prv;
			if (a[j][k] == dirs[3])
				prv = j;
		}
		prv = 1e9;
		for (int j = n - 1; j >= 0; j--) {
			nxt[3][j][k] = prv;
			if (a[j][k] == dirs[1])
				prv = j;
		}
	}
	while (sz(que)) {
		auto [x, y] = que.front();
		que.pop();
		for (int ii = 0; ii < 4; ii++) {
			int nx = (ii % 2 ? nxt[ii][x][y] : x);
			int ny = (ii % 2 ? y : nxt[ii][x][y]);
			if (abs(nx - x) + abs(ny - y) <= k) {
				enq(nx, ny);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (vis[i][j])
				ans++;
		}
	}
	cout << ans << "\n";
}