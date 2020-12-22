#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 63;
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

int n, k, q;
char adj[MAXN][MAXN];
mint dp[MAXN][MAXN][MAXN];
mint upPath[MAXN][MAXN], dnPath[MAXN][MAXN];
mint Fuck[MAXN];

void genUp(int x, int c){
	for(int i=0; i<MAXN; i++){
		for(int j=0; j<MAXN; j++){
			upPath[i][j] = 0;
		}
		Fuck[i] = 0;
	}
	upPath[c][x] = 1;
	for(int i=c+1; i<=k; i++){
		for(int j=0; j<n; j++){
			upPath[i][j] = Fuck[j];
			for(int k=0; k<n; k++){
				upPath[i][j] += upPath[i-1][k] * dp[i-2][k][j];
			}
			Fuck[j] = upPath[i][j];
		}
	}
}

void genDn(int x, int c){
	for(int i=0; i<MAXN; i++){
		for(int j=0; j<MAXN; j++){
			dnPath[i][j] = 0;
		}
		Fuck[i] = 0;
	}
	dnPath[c][x] = 1;
	for(int i=c+1; i<=k; i++){
		for(int j=0; j<n; j++){
			dnPath[i][j] = Fuck[j];
			for(int k=0; k<n; k++){
				dnPath[i][j] += dp[i-2][j][k] * dnPath[i-1][k];
			}
			Fuck[j] = dnPath[i][j];
		}
	}
}

int main(){
	cin >> n >> k >> q;
	for(int i=0; i<n; i++) cin >> adj[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			dp[0][i][j] = (adj[i][j] == '1' ? mint(1) : mint(0));
		}
	}
	for(int i=1; i<=k; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				dp[i][j][k] = dp[i-1][j][k];
				for(int l=0; l<n; l++){
					dp[i][j][k] += dp[i-1][j][l] * dp[i-1][l][k];
				}
			}
		}
	}
	while(q--){
		int x, cx, y, cy;
		cin >> cx >> x >> cy >> y;
		x--; y--;
		genUp(x, cx);
		genDn(y, cy);
		mint ret = 0;
		for(int i = max(cx, cy) + 1; i <= k; i++){
			for(int j=0; j<n; j++){
				ret += upPath[i][j] * dnPath[i][j];
			}
		}
		if(cx == cy && x == y) ret += mint(1);
		if(cx > cy) ret += dnPath[cx][x];
		if(cx < cy) ret += upPath[cy][y];
		cout << ret << endl;
	}
}
