#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 4005;

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
	friend mint inv(const mint &a) {
		assert(a.val);
		return ipow(a, mod - 2);
	}
	mint &operator/=(const mint &m) { return (*this) *= inv(m); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};
#define rend fuck

mint fact[MAXN], invs[MAXN], dp[MAXN][MAXN], s1[MAXN][MAXN], s2[MAXN][MAXN];
int in[MAXN][MAXN], chk[MAXN][MAXN], rend[MAXN], lend[MAXN];

mint solve(vector<pi> v) {
	int l = 1e9, r = -1e9;
	for (auto &[ll, rr] : v) {
		l = min(l, ll);
		r = max(r, rr);
		dp[ll][rr] += invs[sz(v)];
		chk[ll][rr] = 1;
		lend[ll] = rr;
		rend[rr] = ll;
	}

	for (int j = r; j >= l; j--) {
		for (int k = j; k <= r; k++) {
			s1[j][k] = s1[j][k - 1];
			s2[j][k] = s2[j + 1][k];
			if (lend[j] == -1 || rend[k] == -1)
				continue;
			if (k < lend[j])
				continue;
			if (j > rend[k])
				continue;
			if (chk[j][k]) {
				for (int jj = j + 1; jj < k; jj++) {
					if (lend[jj] == -1)
						continue;
					dp[j][k] += s1[jj][k - 1];
				}
				dp[j][k] *= invs[sz(v) - in[j][k]];
				s1[j][k] += dp[j][k];
				s2[j][k] += dp[j][k];
				continue;
			}
			dp[j][k] += s1[j][k - 1] - s1[j][rend[k] - 1];
			dp[j][k] += s2[j + 1][k] - s2[lend[j] + 1][k];
			dp[j][k] *= invs[sz(v) - in[j][k]];
			s1[j][k] += dp[j][k];
			s2[j][k] += dp[j][k];
		}
	}
	mint ret = dp[l][r] * fact[sz(v)];
	return ret;
}

int count_removals(vector<int> S, vector<int> E) {
	int n = sz(S);
	fact[0] = invs[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = fact[i - 1] * mint(i);
		invs[i] = mint(1) / mint(i);
	}
	memset(lend, -1, sizeof(lend));
	memset(rend, -1, sizeof(rend));
	vector<pi> intv(n);
	for (int i = 0; i < n; i++) {
		in[S[i]][E[i]]++;
		intv[i] = {S[i], E[i]};
	}
	for (int i = 2 * n; i >= 1; i--) {
		for (int j = i; j <= 2 * n; j++) {
			in[i][j] += in[i + 1][j] + in[i][j - 1] - in[i + 1][j - 1];
		}
	}
	sort(all(intv));
	vector<int> cnt(n + 1);
	mint ans = 1;
	for (int i = 0; i < n;) {
		int j = i;
		int u = intv[i][1];
		while (j + 1 < n && u >= intv[j + 1][0]) {
			u = max(u, intv[j + 1][1]);
			j++;
		}
		vector<pi> subs(intv.begin() + i, intv.begin() + j + 1);
		ans *= solve(subs);
		cnt[j - i + 1]++;
		i = j + 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= cnt[i]; j++)
			ans *= mint(j);
	}
	return ans.val;
}