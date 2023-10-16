#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
const int MAXN = 50005;
const int mod = 1e9 + 7;
using pi = pair<int, int>;

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

int n, k;
char str[MAXN];
mint dp[MAXN][1 << 6][4];
pi trans[1 << 6][1 << 7][4];

inline int GET(int x, int v){ return (v >= 0 ? ((x >> v) & 1) : 0); }

int main(){
	scanf("%s %d",str,&k);
	n = strlen(str);
	// generate transition table: O(4^K * K^2)
	for(int msk = 0; msk < (1<<(2*k)); msk++){
		for(int mtch = 0; mtch < (2<<(2*k)); mtch++){
			for(int val = 0; val <= k; val++){
				int dp[8];
				fill(dp, dp + 8, -1e9);
				dp[3] = -val;
				for(int w=0; w<k; w++){
					dp[w + 4] = dp[w + 3] + GET(msk, k + w);
					dp[2 - w] = dp[3 - w] - GET(msk, k - 1 - w);
				}
				for(int i=7; i; i--) dp[i] = max(dp[i], dp[i - 1] + GET(mtch, i - 4 + k));
				for(int i=1; i<8; i++) dp[i] = max(dp[i], dp[i-1]);
				int new_dp = 0;
				int new_center = -(dp[4] - 1);
				for(int w=0; w<2*k; w++){
					int pos = w + 4 - k;
					if(dp[pos + 1] != dp[pos]) new_dp |= (1<<w);
				}
				if(new_center >= 0 && new_center <= k) trans[msk][mtch][val] = pi(new_dp, new_center);
				else trans[msk][mtch][val] = pi(-1, -1);
			}
		}
	}
	// DP time
	dp[0][(1 << k) - 1][0] = 1;
	for(int i=0; i<n; i++){
		int msk[26] = {};
		for(int j=0; j<26; j++){
			for(int pos = 0; pos <= 2*k; pos++){
				if(i + pos - k < 0 || i + pos - k >= n) continue;
				if(j + 'A' == str[i + pos - k]) msk[j] |= (1<<pos);
			}
		}
		vector<int> masks;
		for(int i=0; i<26; i++) if(msk[i]) masks.push_back(msk[i]);
		for(int j=0; j<(1<<(2*k)); j++){
			for(int v=0; v<=k; v++){
				if(dp[i][j][v].val == 0) continue;
				for(auto &w : masks){
					auto kek = trans[j][w][v];
					if(~kek.first){
						dp[i + 1][kek.first][kek.second] += dp[i][j][v];
					}
				}
				auto kek = trans[j][0][v];
				if(~kek.first){
					dp[i + 1][kek.first][kek.second] += dp[i][j][v] * mint(26 - sz(masks));
				}
			}
		}
	}
	mint ret = 0;
	for(int j=0; j<(1<<(2*k)); j++){
		for(int v=0; v<=k; v++) ret += dp[n][j][v];
	}
	cout << ret << endl;
}

