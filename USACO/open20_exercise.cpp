#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 7505;
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

int n, moe[MAXN];
mint bino[MAXN][MAXN];
mint fact[MAXN], func[MAXN];

mint solve(int k){
	func[1] = fact[k - 1];
	for(int i=2; i<=n/k; i++){
		func[i] = fact[i * k - 1];
		for(int j=1; j<i; j++){
			func[i] -= func[i-j] * bino[i*k-1][j*k-1] * fact[j*k-1];
		}
	}
	mint ret = 0;
	for(int i=k; i<=n; i+=k){
		ret += fact[n-i] * func[i/k] * bino[n][i];
	}
	return ret;
}

int foo[MAXN];
bool che[MAXN];

int main(){
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	cin >> n >> mod;
	mod -= 1;
	for(int i=0; i<=n; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
		}
	}
	for(int i=2; i<=n; i++){
		for(int j=2*i; j<=n; j+=i) che[j] = 1;
	}
	fact[0] = 1;
	for(int i=1; i<=n; i++) fact[i] = fact[i-1] * mint(i);
	for(int i=2; i<=n; i++){
		if(che[i]) continue;
		mint tmp = 0;
		for(int j=i; j<=n; j*=i){
			//cerr << j << " " << solve(j) << endl;
			tmp += solve(j);
		}
		foo[i] = tmp.val;
	}
	mod += 1;
	mint ans = 1;
	for(int i=2; i<=n; i++){
		if(foo[i]) ans *= ipow(mint(i), foo[i]);
	}
	cout << ans << endl;
}

