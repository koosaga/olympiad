#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 10005;
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

mint dp[MAXN][MAXN / 2];
int balance[MAXN], forcedRemoval[MAXN], adding[MAXN], forcedAdd[MAXN];

int main(){
    cin >> n;
    map<int, int> occur;
    for(int i = 0; i < 2*n; i++){
        string s; cin >> s;
        if(s == "I") a[i].first = +1;
        else a[i].first = -1;
        cin >> a[i].second;
        occur[a[i].second]++;
    }
    vector<pi> tmp;
    for(int i = 0; i < 2*n; i++){
        if(a[i].second && occur[a[i].second] == 2){
            continue;
        }
        tmp.push_back(a[i]);
    }
    n = sz(tmp) / 2;
    for(int i = 0; i < 2*n; i++) a[i] = tmp[i];
    for(int i = 0; i < 2*n; i++){
        balance[i + 1] = balance[i] + a[i].first;
        forcedRemoval[i + 1] = forcedRemoval[i] + (a[i].first == -1 && a[i].second > 0);
        forcedAdd[i + 1] = forcedAdd[i] + (a[i].first == +1 && a[i].second > 0);
        adding[i + 1] = adding[i] + max(a[i].first, 0);
    }
    dp[0][0] = 1;
    for(int i = 0; i < 2*n; i++){
        for(int j = forcedRemoval[i]; j <= forcedRemoval[2*n] && j <= adding[i]; j++){
            if(a[i].first == +1){
                if(a[i].second == 0){
                    dp[i + 1][j + 1] += dp[i][j];
                    int coef1 = n - forcedRemoval[2*n] - (adding[i] - j) - (forcedAdd[2*n] - forcedAdd[i]);
                    if(coef1 > 0){
                        dp[i + 1][j] += mint(coef1) * dp[i][j];
                    }
                }
                else{
                    dp[i + 1][j] += dp[i][j];
                }
            }
            if(a[i].first == -1){
                if(a[i].second == 0){
                    int coef = balance[i] - (j - forcedRemoval[i]);
                    if(coef > 0){
                        dp[i+1][j] += dp[i][j] * mint(coef);
                    }
                }
                else{
                    if(j - forcedRemoval[i] > 0){
                        dp[i + 1][j] += dp[i][j] * mint(j - forcedRemoval[i]);
                    }
                }
            }
        }
    }
    cout << dp[2*n][forcedRemoval[2*n]] << endl;
}

