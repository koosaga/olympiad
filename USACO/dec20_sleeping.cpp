#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 6005;
const int mod = 1e9 + 7;

template<typename T>
T gcd(const T &a, const T &b) {
    return b == T(0) ? a : gcd(b, a % b);
}

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
pi a[MAXN];
mint dp[MAXN][MAXN/2][2];

int main(){
	cin >> n;
	for(int i=0; i<n*2; i++){
		cin >> a[i].first;
		a[i].second = (i < n ? -1 : +1);
	}
	sort(a, a + 2*n);
	dp[0][0][0] = 1;
	for(int i=0; i<2*n; i++){
		for(int j=0; j<=n; j++){
			for(int k=0; k<2; k++){
				if(a[i].second == -1){
					dp[i+1][j+1][k] += dp[i][j][k];
					dp[i+1][j][1] += dp[i][j][k];
				}
				else{
					if(j > 0) dp[i+1][j-1][k] += dp[i][j][k] * mint(j);
					if(k == 0) dp[i+1][j][k] += dp[i][j][k];
				}
			}
		}
	}
	cout << dp[2*n][0][0] + dp[2*n][0][1] << endl;
}
