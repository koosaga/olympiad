#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXN = 605;
const int mod = 1e9 + 7;
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

mint L[MAXN][MAXN][2], R[MAXN][MAXN][2];
mint dp[MAXN][MAXN], bacon[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		auto makeDynamic = [&]() {
			for (int i = 0; i <= sz(s); i++) {
				for (int j = 0; j <= i; j++)
					dp[i][j] = 0;
			}
			dp[0][0] = 1;
			vector<int> nl(sz(s) + 1, sz(s)), nr(sz(s) + 1, sz(s));
			for (int i = sz(s) - 1; i >= 0; i--) {
				if (s[i] == 'L')
					nl[i] = i;
				else
					nl[i] = nl[i + 1];
				if (s[i] == 'P')
					nr[i] = i;
				else
					nr[i] = nr[i + 1];
			}
			for (int i = 0; i < sz(s); i++) {
				for (int j = 0; j <= i; j++) {
					if (nl[i] < sz(s))
						dp[nl[i] + 1][j + 1] += dp[i][j];
					if (j && nr[i] < sz(s))
						dp[nr[i] + 1][j - 1] += dp[i][j];
				}
			}
		};
		makeDynamic();
		int lcnt = 0, pcnt = 0;
		for (int l = sz(s); l >= 0; l--) {
			for (int j = 0; j <= l; j++) {
				if (lcnt == 0)
					L[i][j][0] += dp[l][j];
				if (pcnt == 0)
					L[i][j][1] += dp[l][j];
			}
			if (l > 0)
				bacon[i] += dp[l][0];
			if (l && s[l - 1] == 'L')
				lcnt++;
			if (l && s[l - 1] == 'P')
				pcnt++;
		}
		reverse(all(s));
		for (auto &x : s)
			x = 'L' + 'P' - x;
		makeDynamic();
		for (int l = sz(s); l > 0; l--) {
			for (int j = 0; j <= l; j++) {
				if (s[l - 1] == 'P')
					R[i][j][0] += dp[l][j];
				if (s[l - 1] == 'L')
					R[i][j][1] += dp[l][j];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mint ret = bacon[i];
			for (int k = 0; k < MAXN; k++)
				ret += L[i][k][0] * R[j][k][0] + L[i][k][1] * R[j][k][1];
			cout << ret << " ";
		}
		cout << "\n";
	}
}