#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 1e9 + 7;
const int MAXN = 300005;
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

string s, p;
int n, k, c[MAXN];

struct node {
	vector<lint> a[3][3];
	lint base[3][3];
};

lint dp[10][10];

node solve(int l, int r) {
	if (r - l <= 8) {
		node ret;
		for (int x = 0; x < sz(p); x++) {
			for (int y = 0; y < sz(p); y++) {
				int ll = l, rr = r;
				lint sum = 0;
				for (int j = (x ? x : sz(p)); j < sz(p); j++) {
					if (p[j] != s[ll])
						sum += c[ll];
					ll++;
				}
				for (int j = y - 1; j >= 0; j--) {
					rr--;
					if (p[j] != s[rr])
						sum += c[rr];
				}
				int B = (rr - ll) / sz(p) + 1;
				for (int j = 0; j < B; j++)
					dp[0][j] = (j ? 1e18 : sum);
				for (int i = 1; i <= rr - ll; i++) {
					for (int j = 0; j < B; j++)
						dp[i][j] = dp[i - 1][j];
					if (i >= sz(p)) {
						for (int j = 1; j < B; j++) {
							lint up = dp[i - sz(p)][j - 1];
							for (int k = 0; k < sz(p); k++) {
								if (s[i + ll - sz(p) + k] != p[k])
									up += c[i + ll - sz(p) + k];
							}
							dp[i][j] = min(dp[i][j], up);
						}
					}
				}
				ret.base[x][y] = dp[rr - ll][0];
				for (int i = 1; i < B && dp[rr - ll][i] < 1e17; i++) {
					ret.a[x][y].push_back(dp[rr - ll][i] - dp[rr - ll][i - 1]);
				}
			}
		}
		return ret;
	}
	int m = (l + r) / 2;
	auto i1 = solve(l, m);
	auto i2 = solve(m, r);
	node ret;
	for (int i = 0; i < sz(p); i++) {
		for (int j = 0; j < sz(p); j++) {
			vector<lint> reals;
			auto put = [&](int k, lint v) {
				while (sz(reals) <= k)
					reals.push_back(1e18);
				reals[k] = min(reals[k], v);
			};
			for (int k = 0; k < sz(p); k++) {
				lint sum = i1.base[i][k] + i2.base[k][j];
				int p1 = 0, p2 = 0;
				put((k ? 1 : 0) + p1 + p2, sum);
				while (p1 < sz(i1.a[i][k]) || p2 < sz(i2.a[k][j])) {
					if (p2 == sz(i2.a[k][j]) || (p1 < sz(i1.a[i][k]) && i1.a[i][k][p1] < i2.a[k][j][p2])) {
						sum += i1.a[i][k][p1++];
					} else {
						sum += i2.a[k][j][p2++];
					}
					put((k ? 1 : 0) + p1 + p2, sum);
				}
			}
			assert(reals[0] <= reals[1]);
			for (int k = 1; k < sz(reals); k++) {
				ret.a[i][j].push_back(reals[k] - reals[k - 1]);
			}
			ret.base[i][j] = reals[0];
			assert(is_sorted(all(ret.a[i][j])));
		}
	}
	return ret;
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> k >> n >> s;
	for (int i = 0; i < k; i++)
		p.push_back(i ? 'O' : 'M');
	for (int i = 0; i < n; i++)
		cin >> c[i];
	auto ans = solve(0, n);
	lint sum = ans.base[0][0];
	for (int i = 1; i <= n / sz(p); i++) {
		sum += ans.a[0][0][i - 1];
		cout << sum << "\n";
	}
}