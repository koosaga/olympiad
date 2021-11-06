#include <bits/stdc++.h>
#define sz(v)((int)(v).size())
#define all(v)(v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using point = complex<llf>;
using pi = pair<lint, lint>;
const int MAXN = 1005;
const int mod = 1e6 + 3;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct mint {
	int val;
	mint(){ val = 0; }
	mint(const lint& v){
		val =(-mod <= v && v < mod) ? v : v % mod;
		if(val < 0) val += mod;
	}

	friend ostream& operator<<(ostream& os, const mint& a){ return os << a.val; }
	friend bool operator==(const mint& a, const mint& b){ return a.val == b.val; }
	friend bool operator!=(const mint& a, const mint& b){ return !(a == b); }
	friend bool operator<(const mint& a, const mint& b){ return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint& operator+=(const mint& m){ if((val += m.val) >= mod) val -= mod; return *this; }
	mint& operator-=(const mint& m){ if((val -= m.val) < 0) val += mod; return *this; }
	mint& operator*=(const mint& m){ val =(lint)val*m.val%mod; return *this; }
	friend mint ipow(mint a, lint p){
		mint ret = 1; for(; p; p /= 2, a *= a) if(p&1) ret *= a;
		return ret;
	}
	friend mint inv(const mint& a){ assert(a.val); return ipow(a, mod - 2); }
	mint& operator/=(const mint& m){ return(*this) *= inv(m); }

	friend mint operator+(mint a, const mint& b){ return a += b; }
	friend mint operator-(mint a, const mint& b){ return a -= b; }
	friend mint operator*(mint a, const mint& b){ return a *= b; }
	friend mint operator/(mint a, const mint& b){ return a /= b; }
	operator int64_t() const {return val; }
};


void solve(){
	vector<int> rk[205];
	int n; cin >> n;
	for(int i = 1; i <= n; i++){
		int x; cin >> x;
		rk[x].push_back(i);
	}
	vector<int> fuck;
	vector<int> v;
	for(int i = 1; i <= 200; i++){
		if(sz(rk[i]) == 6){
			for(auto &j : rk[i]) fuck.push_back(j);
		}
	}
	sort(all(fuck));
	for(int i = 1; i <= 200; i++){
		if(sz(rk[i]) == 6){
			v.push_back(i);
			rk[i].pop_back();
			for(auto &j : rk[i]){
				j = lower_bound(all(fuck), j) - fuck.begin() + 1;
			}
		}
	}
	cout << *min_element(all(v), [&](const int a, const int b){
		return 
		pi(accumulate(all(rk[a]), 0) - rk[a][4], rk[a][4]) < 
		pi(accumulate(all(rk[b]), 0) - rk[b][4], rk[b][4]);
	}) << endl;
}
int main(){
	int tc; scanf("%d",&tc);
	for(int i = 1; i <= tc; i++){
	//	printf("Case #%d: ", i);
		solve();
	}
}

