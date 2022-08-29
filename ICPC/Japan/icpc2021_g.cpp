#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 305;

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
mint dp[MAXN][MAXN][MAXN];

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++) cin >> x[i] >> y[i];
    dp[n][0][0] = 1;
    // dp(pos, canChild, wantChild)
    for(int i = n - 1; i >= 0; i--){
        for(int d = x[i]; d <= y[i]; d++){
            if(d == 0){
                for(int j = 0; j <= n; j++){
                    for(int k = 0; k <= n; k++){
                        dp[i][j][k] += dp[i + 1][j][k + 1] * mint(k + 1);
                        dp[i][j + 1][k] += dp[i + 1][j][k];
                    }
                }
            }
            if(d == 1){
                for(int j = 0; j <= n; j++){
                    for(int k = 0; k <= n; k++){
                        dp[i][j][k] += dp[i + 1][j + 1][k + 1] * mint(j + 0) * mint(k + 1) * mint(2);
                        dp[i][j + 1][k] += dp[i + 1][j + 1][k] * mint(j + 1) * mint(2);
                    }
                }
            }
            if(d == 2){
                for(int j = 0; j <= n; j++){
                    for(int k = 0; k <= n; k++){
                        // two childs from back, be a child of back
                        dp[i][j][k] += dp[i + 1][j + 2][k + 1] * mint((j + 1) * (j + 0)) * mint(k + 1);
                        dp[i][j + 1][k] += dp[i + 1][j + 2][k] * mint((j + 1) * (j + 2));
                        dp[i][j][k + 1] += dp[i + 1][j + 1][k + 1] * mint(j + 0) * mint(k + 1) * mint(2);
                        dp[i][j + 1][k + 1] += dp[i + 1][j + 1][k]* mint(j + 1) * mint(2);
                    }
                }
            }
        }
    }
    cout << dp[0][1][0] << "\n";
}
