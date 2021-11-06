#include <bits/stdc++.h>
#define sz(v)((int)(v).size())
#define all(v)(v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using point = complex<llf>;
using pi = pair<lint, lint>;
const int MAXN = 2005;
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

char buf[MAXN];
void solve(){
	int n;
	scanf("%d\n",&n);
	fgets(buf, MAXN, stdin);
	vector<int> v;
	int s = 0;
	for(int i = 0; buf[i]; i++){
		if(isspace(buf[i])){
			if(s) v.push_back(s + 1);
			s = 0;
		}
		else s++;
	}
	int ans = 0;
	for(int i = 0; i < sz(v); ){
		int j = i;
		int sum = -1;
		while(j < sz(v) && sum + v[j] <= n) sum += v[j++];
		i = j;
		ans++;
	}
	cout << ans << endl;
}

int main(){
	int tc; scanf("%d",&tc);
	for(int i = 1; i <= tc; i++){
	//	printf("Case #%d: ", i);
		solve();
	}
}
