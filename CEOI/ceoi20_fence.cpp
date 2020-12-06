// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 1000005;
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
}sum[MAXN];
 
int n;
pi a[MAXN];
int L[MAXN], R[MAXN];
 
mint f(mint x){
	return x * (x + mint(1)) * mint((mod + 1) / 2);
}
 
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%lld",&a[i].first);
	for(int i=1; i<=n; i++) scanf("%lld",&a[i].second);
	for(int i=1; i<=n; i++) sum[i] = sum[i-1] + mint(a[i].second);
	vector<int> stk = {0};
	for(int i=1; i<=n; i++){
		while(sz(stk) && a[stk.back()].first > a[i].first) stk.pop_back();
		L[i] = stk.back() + 1;
		stk.push_back(i);
	}
	stk.clear();
	stk.push_back(n + 1);
	for(int i=n; i; i--){
		while(sz(stk) && a[stk.back()].first >= a[i].first) stk.pop_back();
		R[i] = stk.back() - 1;
		stk.push_back(i);
	}
	mint ret = 0;
	for(int i=1; i<=n; i++){
		mint l = sum[i - 1] - sum[L[i] - 1];
		mint m = a[i].second;
		mint r = sum[R[i]] - sum[i];
		mint h = a[i].first;
		ret += f(h) * (f(l+m+r) - f(l) - f(r));
	}
	cout << ret << endl;
}
