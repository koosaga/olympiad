#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 2005;
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

int n;
char str[MAXN][MAXN];
mint dp[MAXN][MAXN][2], pwr[MAXN];
int S1[MAXN][MAXN], S2[MAXN][MAXN];

int main(){
	freopen("sprinklers2.in", "r", stdin);
	freopen("sprinklers2.out", "w", stdout);
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	pwr[0] = 1;
	for(int i=1; i<=n; i++) pwr[i] = pwr[i-1] + pwr[i-1];
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			if(i) S1[i][j] = S1[i-1][j] + (str[i-1][j] == '.');
			if(j) S2[i][j] = S2[i][j-1] + (str[i][j-1] == '.');
		}
	}
	for(int i=n; i>=0; i--){
		for(int j=n; j>=0; j--){
			if(i == n && j == n){
				dp[n][n][0] = dp[n][n][1] = 1;
				continue;
			}
			dp[i][j][0] = dp[i+1][j][0] * pwr[S2[i][j]];
			dp[i][j][1] = dp[i][j+1][1] * pwr[S1[i][j]];
			if(i && str[i-1][j] == '.'){
				dp[i][j][0] += dp[i][j+1][1] * pwr[S1[i][j] - 1];
			}
			if(j && str[i][j-1] == '.'){
				dp[i][j][1] += dp[i+1][j][0] * pwr[S2[i][j] - 1];
			}
		}
	}
	cout << dp[1][0][0] + dp[0][1][1] << endl;
}

