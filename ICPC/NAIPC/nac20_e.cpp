#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
int mod;

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

int n, m;
mint dp[2][1<<12][13];
int nxt[13][13][1<<12];

int main(){
	cin >> n >> m >> mod;
	if(n%2 && m%2){
		puts("1");
		return 0;
	}
	if(n%2 || m%2){
		if(n%2 > m%2) swap(n, m);
		n /= 2, m /= 2;
		cout << ipow(mint(n + 1), m) << endl;
		return 0;
	}
		n /= 2, m /= 2;
	for(int i=0; i<(1<<n); i++){
		for(int j=0; j<=n; j++){
			dp[0][i][j] = 1;
		}
	}
	for(int x = 0; x <= n; x++){
		for(int y = 0; y <= n; y++){
			for(int j=0; j<(1<<n); j++){
				int new_msk = j;
				for(int k = x; k+1 < y; k++){
					if(((j >> k) & 3) == 1) new_msk ^= (1<<k);
				}
				for(int k = y; k+1 < x; k++){
					if(((j >> k) & 3) == 2) new_msk ^= (1<<(k+1));
				}
				nxt[x][y][j] = new_msk;
			}
		}
	}
	for(int i=0; i<m-1; i++){
		for(int y = 0; y <= n; y++){
			mint val[1 << 12] = {};
			for(int x = 0; x <= n; x++){
				for(int j=0; j<(1<<n); j++){
					val[nxt[x][y][j]] += dp[i%2][j][x];
				}
			}
			for(int i=n-1; i>=0; i--){
				for(int j=0; j<(1<<n); j++){
					if((j >> i) & 1) val[j ^ (1<<i)] += val[j];
				}
			}
			for(int j=0; j<(1<<n); j++){
				dp[(i+1)%2][j][y] += val[j];
			}
		}
		for(int j=0; j<(1<<n); j++){
			for(int k=0; k<=n; k++){
				dp[i%2][j][k] = 0;
			}
		}
	}
	mint ret = 0;
	for(int i=0; i<(1<<n); i++){
		for(int j=0; j<=n; j++){
			ret += dp[(m-1)%2][i][j];
		}
	}
	cout << ret << endl;
}

