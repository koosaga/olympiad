#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 50005;
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

mint dp[500][MAXN];

int main(){
	dp[0][0] = 1;
	for(int i = 1; i < 500; i++){
		for(int j = 0; j < MAXN; j++){
			dp[i][j] = dp[i-1][j];
			if(j >= i) dp[i][j] += dp[i-1][j-i];
		}
	}
	for(int i = 1; i < 500; i++){
		for(int j = 1; j < MAXN; j++){
			dp[i][j] += dp[i][j-1];
		}
	}
	int q; scanf("%d",&q);
	while(q--){
		int a, b; scanf("%d %d",&a,&b);
		mint ret = 0;
		for(int i = 1; i * (i + 1) / 2 <= a + b; i++){
			int lo = i * (i + 1) / 2 - b;
			ret += dp[i][a];
			if(lo > 0) ret -= dp[i][lo-1];
		}
		printf("%lld\n", (lint)ret);
	}
}

