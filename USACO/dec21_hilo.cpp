#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 5005;
const int mod = 1e9 + 7;

struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }

    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};

pair<mint, mint> dp[2][MAXN][2];
mint invs[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, x; cin >> n >> x;
	x = n - x;
	for(int i = 1; i <= n; i++) invs[i] = mint(1) / mint(i);
	for(int i = x; i >= 0; i--){
		int X = i % 2;
		int Y = (i + 1) % 2;
		for(int j = 0; j <= n; j++) dp[X][j][0] = dp[X][j][1] = make_pair(mint(0), mint(0));
		for(int j = x; j <= n; j++){
			if(i == x && j == x){
				dp[X][j][0].first = 1;
				continue;
			}
			mint b = invs[j - i];
			if(i < x){
				mint q = mint(max(j - i - 1, 1)) * b;
				if(i + 1 != j){
					dp[X][j][0] = dp[Y][j][0];
					dp[X][j][0].first *= q;
					dp[X][j][0].second *= q;
				}
				dp[X][j][0].first += dp[Y][j][0].first * b;
				dp[X][j][0].second += dp[Y][j][0].second * b;
				dp[X][j][0].first += dp[Y][j][1].first * b;
				dp[X][j][0].second += dp[Y][j][1].second * b;
				dp[X][j][0].second += dp[Y][j][1].first * b;
			}
			if(j > x){
				mint q = mint(max(j - i - 1, 1)) * b;
				dp[X][j][1] = dp[X][j - 1][1];
				dp[X][j][1].first *= q;
				dp[X][j][1].second *= q;
				dp[X][j][1].first += dp[X][j - 1][0].first * b;
				dp[X][j][1].second += dp[X][j - 1][0].second * b;
				dp[X][j][1].first += dp[X][j - 1][1].first * b;
				dp[X][j][1].second += dp[X][j - 1][1].second * b;
			}
		}
	}
	mint q = (dp[0][n][0].second + dp[0][n][1].second);
	for(int i = 1; i <= n; i++) q *= mint(i);
	cout << q << '\n';
}
