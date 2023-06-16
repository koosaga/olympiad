#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 4005;
const int mod = 1e9 + 7; // 993244853;

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

mint fact[MAXN], invf[MAXN];
int n, k;

int cnt[MAXN];
pi s[MAXN];
int sub[MAXN], supply[MAXN];

void prep(int x) {
	sub[x] = 1;
	supply[x] = cnt[x];
	for (int i = 0; i < 2; i++) {
		if (s[x][i]) {
			prep(s[x][i]);
			sub[x] += sub[s[x][i]];
			supply[x] += supply[s[x][i]];
		}
	}
}

mint dp[MAXN][MAXN];

mint binom(int a, int b) { return fact[a + b] * invf[a] * invf[b]; }

void dfs(int x, int prv = -1) {
	for (int i = 0; i < 2; i++) {
		if (s[x][i])
			dfs(s[x][i], i);
	}
	int canSendL = sub[s[x][0]] - supply[s[x][0]];
	int canSendR = sub[s[x][1]] - supply[s[x][1]];
	for (int a = 0; a <= cnt[x]; a++) {
		int b = cnt[x] - a;
		if (a > canSendL || b > canSendR)
			continue;
		for (int i = 0; i <= k; i++) {
			if (x == 1 && i > 0)
				break;
			int upLeft = canSendL - a;
			int upRight = canSendR - b;
			if (i >= upLeft + upRight + 1)
				break;
			if (prv == 0) {
				int L = min(upLeft, i);
				int R = i - L;
				dp[x][i] += dp[s[x][0]][a + L] * dp[s[x][1]][b + R] * binom(a, b) * binom(L, R);
			} else {
				int R = min(upRight, i);
				int L = i - R;
				dp[x][i] += dp[s[x][0]][a + L] * dp[s[x][1]][b + R] * binom(a, b) * binom(L, R);
			}
		}
	}
	// retarded case: i + cnt[x] == canSendL + canSendR + 1
	int ass = canSendL + canSendR + 1 - cnt[x];
	if (ass >= 0) {
		dp[x][ass] += dp[s[x][0]][canSendL] * dp[s[x][1]][canSendR] * binom(canSendL, canSendR) * mint(canSendL + canSendR + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fact[0] = invf[0] = 1;
	for (int i = 1; i < MAXN; i++)
		fact[i] = fact[i - 1] * mint(i), invf[i] = mint(1) / fact[i];
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	for (int i = 1; i <= n; i++)
		cin >> s[i][0] >> s[i][1];
	prep(1);
	for (int i = 1; i <= n; i++) {
		if (supply[i] > sub[i]) {
			cout << "0\n";
			return 0;
		}
	}
	dp[0][0] = 1; // haha, funny
	dfs(1);
	cout << dp[1][0] << "\n";
}
