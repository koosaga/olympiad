#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 5005;
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

int toMove[2][MAXN];
mint dp[MAXN][MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t; cin >> t;
	for(int i = 0; i < t; i++){
		vector<pi> v[2];
		int n; cin >> n;
		for(int j = 0; j < n; j++){
			int x; cin >> x;
			v[x % 2].emplace_back(j, x);
		}
		memset(toMove, 0, sizeof(toMove));
		for(int i = 0; i < sz(v[0]); i++){
			for(int j = 0; j < sz(v[1]); j++){
				if(abs(v[0][i].second - v[1][j].second) > 1){
					if(v[0][i].first < v[1][j].first){
						toMove[1][j] = max(toMove[1][j], i + 1);
					}
					else{
						toMove[0][i] = max(toMove[0][i], j + 1);
					}
				}
			}
		}
		dp[0][0] = 1;
		for(int i = 0; i <= sz(v[0]); i++){
			for(int j = 0; j <= sz(v[1]); j++){
				if(i < sz(v[0])){
					if(toMove[0][i] <= j) dp[i + 1][j] += dp[i][j];
				}
				if(j < sz(v[1])){
					if(toMove[1][j] <= i) dp[i][j + 1] += dp[i][j];
				}
			}
		}
		cout << dp[sz(v[0])][sz(v[1])] << endl;
		for(int i = 0; i <= sz(v[0]); i++){
			for(int j = 0; j <= sz(v[1]); j++){
				dp[i][j] = 0;
			}
		}
	}
}
