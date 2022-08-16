#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 10005;
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

mint bino[MAXN][MAXN];
mint sum[MAXN][MAXN];

mint insec(pair<int, string> a, pair<int, string> b, pair<int, string> c){
    int n = sz(a.second);
    vector<int> z1, z2;
    for(int i = 0; i < n; i++){
        if(a.second[i] != b.second[i]){
            z2.push_back(a.second[i] ^ c.second[i]);
        }
        else{
            z1.push_back(a.second[i] ^ c.second[i]);
        }
    }
    int C1 = count(all(z1), 1);
    int C2 = count(all(z2), 1);
    for(int i = 0; i <= C2; i++){
        for(int j = 0; j <= sz(z2) - C2; j++){
            sum[j - i + C2][i + j + 1] += bino[C2][i] * bino[sz(z2) - C2][j];

        }
    }
    for(int i = 0; i <= sz(z2) + 2; i++){
        for(int j = 1; j <= sz(z2) + 2; j++){
            sum[i][j] += sum[i][j - 1];
        }
    }
    for(int i = 1; i <= sz(z2) + 2; i++){
        for(int j = 0; j <= sz(z2) + 2; j++){
            sum[i][j] += sum[i - 1][j];
        }
    }
    mint ret = 0;
    for(int A = 0; A <= sz(z1); A++){
        for(int x = 0; A + x <= sz(z1); x++){
            int sumR = a.first - A - x;
            int sumL = sz(z2) - b.first + (A + x);
            int subUp = c.first - C1 - C2 - (x - A) + C2;
            subUp = min(subUp, sz(z2) + 2);
            if(subUp >= 0){
                sumL = max(sumL, 0);
                sumR = min(sumR, sz(z2));
                if(sumL <= sumR) ret += (sum[subUp][sumR + 1] - sum[subUp][sumL]) * bino[C1][A] * bino[sz(z1) - C1][x];
            }
        }
    }
    for(int i = 0; i <= sz(z2) + 2; i++){
        for(int j = 0; j <= sz(z2) + 2; j++){
            sum[i][j] = 0; 
        }
    }
    return ret;
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++){
        bino[i][0] = 1;
        for(int j = 1; j <= i; j++){
            bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
        }
    }
        vector<pair<int, string>> v(3);
        for(int i = 0; i < 3; i++){
            cin >> v[i].first >> v[i].second;
        }
        pair<int, string> w(n, string(n, '0'));
        mint ret = 0;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j <= v[i].first; j++) ret += bino[n][j];
            ret -= insec(v[i], v[(i + 1) % 3], w);
        }
        ret += insec(v[0], v[1], v[2]);
        cout << ret << "\n";
}
