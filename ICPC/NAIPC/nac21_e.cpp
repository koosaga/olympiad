#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
using pi = pair<int, int>;
using lint = long long;
const int mod = 998244353;

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
char str[MAXN];
mint val[MAXN], dp[MAXN];
int d1[MAXN], d2[MAXN], sum[MAXN];

int f(int x, int y){
	if(str[x] == '?' && str[y] == '?') return 1;
	if(str[x] != '?' && str[y] != '?' && str[x] != str[y]) return -32000;
	return 0;
}

int rf(int x, int y){
	return f(n-1-x, n-1-y);
}

int main(){
	scanf("%s", str);
	n = strlen(str);
	val[0] = 1;
	for(int i = 1; i <= n; i++){
		val[i] = val[i-1] * mint(26);
		sum[i] = sum[i - 1] + (str[i-1] == '?');
	}
	for(int i = n / 2; i >= 0; i--){
		dp[i] = val[sum[n - i] - sum[i]];
		for(int j = 0; j < n; j++){
			if(i + j < n - 1){
				d1[j] = d1[j + 1] + f(i, j);
				d2[j] = d2[j + 1] + rf(i, j);
			}
		}
		for(int j = i + 1; j <= n / 2; j++){
			int fn = d1[n - j] + d2[n - j];
			if(j % 2 != i % 2) fn += f((i + j) / 2, n - 1 - (i + j) / 2);
			if(fn >= 0) dp[i] += dp[j] *  val[fn];
		//	if(fn >= 0) printf("%d %d %d\n", i, j, fn);
		}
	}
	cout << dp[0] << endl;
}
