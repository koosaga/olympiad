#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1005;
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
 
int n;
struct mtrx{
	mint adj[MAXN][MAXN];
	mtrx operator*(const mtrx &b){
		mtrx c;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				c.adj[i][j] = 0;
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					c.adj[j][k] += adj[j][i] * b.adj[i][k];
				}
			}
		}
		return c;
	}
};
 
mtrx ret, A;
 
void solve_K(int q){
	if(q == 0){
		memset(ret.adj, 0, sizeof(ret.adj));
		for(int i=0; i<n; i++) ret.adj[i][i] = mint(1);
		return;
	}
	if(q % 2 == 1){
		solve_K(q - 1);
		A = ret;
		memset(ret.adj, 0, sizeof(ret.adj));
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=-1; k<=1; k++){
					if(j + k < 0 || j + k >= n) continue;
					ret.adj[i][j] += A.adj[i][j + k];
				}
			}
		}
		return;
	}
	solve_K(q >> 1);
	A = ret;
	memset(ret.adj, 0, sizeof(ret.adj));
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			ret.adj[i][0] += A.adj[i][j] * A.adj[j][0];
		}
		ret.adj[0][i] = ret.adj[i][0];
	}
	for(int i=1; i<n; i++){
		for(int j=1; j<n; j++){
			if(i + j < n) ret.adj[i][j] = ret.adj[i-1][j-1] + ret.adj[0][i + j];
		}
	}
	for(int i=n-1; i; i--){
		for(int j=n-1; j; j--){
			if(i + j >= n) ret.adj[i][j] = ret.adj[n-1-i][n-1-j];
		}
	}
}
 
int OneTime(int x1, int y1, int x2, int y2){
	return y1 == y2 || x1 == x2 || abs(x1 - x2) == abs(y1 - y2);
}
 
mint bino(int x, int y){
	mint ret = 1;
	mint inv = 1;
	for(int i=1; i<=y; i++) ret *= mint(x+1-i);
	for(int i=1; i<=y; i++) inv *= mint(i);
	return ret / inv;
}

pair<int, mint> solve(int r, int x, int y){
	if(abs(x - y) % 2 != (r - 1) % 2) return make_pair(0, mint(0));
	if(r == 1) return make_pair(0, mint(1));
	if(abs(x - y) == r - 1) return make_pair(1, mint(1));
	auto dom = [&](int k){
		assert(k >= 2);
		k -= 2;
		if(k % 2 == 0){
			return make_pair(1ll * (n-1) * k + 3, x);
		}
		return make_pair(1ll * (n-1) * k + 3, n - 1 - x);
	};
	auto in_hood = [&](pi p, pi q){
		return q.first - p.first >= abs(q.second - p.second);
	};
	int s = 2, e = 1e9;
	while(s != e){
		int m = (s+e+1)/2;
		if(in_hood(dom(m), pi(r, y))) s = m;
		else e = m - 1;
	}
	auto p = dom(s);
	pair<int, mint> ret(s, mint(0));
	{
		int s = 0, e = y;
		while(s != e){
			int m = (s + e + 1) / 2;
			if(in_hood(p, pi(r - m, y - m))) s = m;
			else e = m - 1;
		}
		if(s != y){
			int slack = y - s - 1;
			ret.second += bino(slack + ret.first - 2, slack);
		}
	}
	{
		int s = 0, e = n - 1 - y;
		while(s != e){
			int m = (s + e + 1) / 2;
			if(in_hood(p, pi(r - m, y + m))) s = m;
			else e = m - 1;
		}
		if(s != n-1-y){
			int slack = n-1-y - s - 1;
			ret.second += bino(slack + ret.first - 2, slack);
		}
	}
	return ret;
}

int main(){
	int r, q;
	cin >> r >> n >> q;
	mtrx K, B;
	solve_K(r - 1);
	K = ret;
	while(q--){
		char t[5]; int x, y;
		cin >> t >> x >> y;
		x--; y--;
		if(*t == 'B'){
			auto dap = solve(r, x, y);
			printf("%d %lld\n", dap.first, (lint)dap.second);
		}
		if(*t == 'P'){
			if(x == y) printf("%d 1\n", r - 1);
			else printf("0 0\n");
		}
		if(*t == 'R'){
			if(x == y) printf("1 1\n");
			else printf("2 2\n");
		}
		if(*t == 'Q'){
			if(OneTime(1, x, r, y)) printf("1 1\n");
			else{
				if(r > n) printf("2 4\n");
				else{
					int ret = 0;
					for(int i=1; i<=r; i++){
						for(int j=0; j<n; j++){
							if(OneTime(1, x, i, j) && OneTime(i, j, r, y)) ret++;
						}
					}
					printf("2 %d\n", ret);
				}
			}
		}
		if(*t == 'K'){
			printf("%d %lld\n", r - 1, (lint)K.adj[x][y]);
		}
	}
}

