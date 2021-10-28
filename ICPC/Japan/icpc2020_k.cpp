#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;
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

int l;
string s;
int fail[MAXN], sum[MAXN];
int dp[MAXN][MAXN];

bool vis[MAXN][129];
pi mem[MAXN][129];

pi getnext(int y, int chr){
    if(vis[y][chr]) return mem[y][chr];
    vis[y][chr] = 1;
    int ny = y;
    int nret = 0;
    if(ny == sz(s)){
        nret += ny + sum[ny - fail[ny] - 1];
        ny = fail[ny];
    }
    while(ny && s[ny] != chr){
        nret += ny + sum[ny - fail[ny] - 1];
        ny = fail[ny];
    }
    if(s[ny] == chr) ny++;
    return mem[y][chr] = pi(nret, ny);
}

int f(int x, int y){
    if(x == l){
        int ret = getnext(y, 0).first;
        return ret;
    }
    if(~dp[x][y]) return dp[x][y];
    int ret = 0;
    for(int i = 'a'; i <= 'z'; i++){
        pi qq = getnext(y, i);
        ret = max(ret, qq.first + f(x + 1, qq.second));
    }
    return dp[x][y] = ret;
}

int main(){
    cin >> s >> l;
    int p = 0;
    for(int i = 1; i < sz(s); i++){
        while(p && s[i] != s[p]) p = fail[p];
        if(s[i] == s[p]) p++;
        fail[i + 1] = p;
    }
    for(int i = 1; i < sz(s); i++){
        sum[i] = sum[i - 1];
        for(int j = 0; j + i < sz(s); j++){
            if(s[j] == s[j + i]) sum[i]++;
            else break;
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << f(0, 0) << endl;
}
