#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 1000005;
 
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
 
lint fuck = 5e12;
 
int n;
 
int ceil_insec(pi a, pi b, int x){
	if(a.first == b.first) return 1e9;
	lint A = a.second * (b.first - a.first) + (x - a.first) * (b.second - a.second);
	lint B = b.first - a.first;
	lint modular = ((A % B) + B) % B;
	if(modular) A += B - modular;
	return A / B;
}
 
int floor_insec(pi a, pi b, int x){
	assert(a.first != b.first);
	lint A = a.second * (b.first - a.first) + (x - a.first) * (b.second - a.second);
	lint B = b.first - a.first;
	lint modular = ((A % B) + B) % B;
	A -= modular;
	return A / B;
}
 
mint fact[MAXN * 2], invf[MAXN * 2];
 
mint binom(int x, int y){
	if(y < 0 || y > x) return mint(0);
	return fact[x] * invf[x-y] * invf[y];
}
 
lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}
 
int main(){
	fact[0] = mint(1);
	for(int i=1; i<MAXN*2; i++){
		fact[i] = fact[i-1] * mint(i);
	}
	invf[MAXN*2-1] = mint(1) / fact[MAXN*2-1];
	for(int i=MAXN*2-2; i>=0; i--) invf[i] = invf[i + 1] * mint(i + 1);
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		pi a[3];
		for(int j=0; j<3; j++){
			scanf("%lld %lld",&a[j].second, &a[j].first);
		}
		sort(a, a + 3);
		if(ccw(a[0], a[1], a[2]) < 0){
			for(int j=0; j<3; j++){
				a[j].second *= -1;
			}
		}
		if(a[2].first < 0){
			puts("0");
			continue;
		}
		vector<int> L(MAXN), R(MAXN);
		fill(all(L), 1e9);
		fill(all(R), -1e9);
		for(int i = a[0].first; i <= a[1].first; i++){
			if(i >= 0){
				L[i] = min(ceil_insec(a[0], a[1], i), L[i]);
			}
		}
		for(int i = a[1].first; i <= a[2].first; i++){
			if(i >= 0){
				L[i] = min(ceil_insec(a[1], a[2], i), L[i]);
			}
		}
		for(int i = a[0].first; i <= a[2].first; i++){
			if(i >= 0) R[i] = floor_insec(a[0], a[2], i);
		}
		int s = max(0ll, a[0].first);
		int e = min(1000000ll, a[2].first);
		for(int i = s; i <= e; i++){
			L[i] += i;
			R[i] += i;
			L[i] = (L[i] + 1) / 2;
			if(R[i] < 0) R[i] = -69;
			R[i] /= 2;
			L[i] = max(L[i], 0);
			R[i] = min(R[i], i);
		}
		pi prv(1, 0);
		mint cur;
		mint dap;
		for(int i = s; i <= e; i++){
			if(L[i] > R[i]){
				prv = pi(L[i], R[i]);
				cur = 0;
				continue;
			}
			if(prv.first > prv.second){
				cur = 0;
				for(int j = L[i]; j <= R[i]; j++) cur += binom(i, j);
				prv = pi(L[i], R[i]);
			}
			else{
				cur = cur + cur - binom(i - 1, prv.second) + binom(i - 1, prv.first - 1);
				while(L[i] < prv.first) cur += binom(i, --prv.first);
				while(R[i] > prv.second) cur += binom(i, ++prv.second);
				while(L[i] > prv.first) cur -= binom(i, prv.first++);
				while(R[i] < prv.second) cur -= binom(i, prv.second--);
			}
			dap += cur;
			//printf("%d:%d %d\n", i, L[i], R[i]);
		}
		cout << dap << endl;
	}
}
 