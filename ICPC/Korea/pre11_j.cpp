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

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x > e.x;
	}
};

void solve(){
	int n, m, s, e;
	scanf("%d %d %d %d",&n,&m,&s,&e);
	vector<edg> ed(m);
	for(auto &i : ed){
		scanf("%d %d %d",&i.s,&i.e,&i.x);
	}
	sort(all(ed));
	disj.init(n);
	for(auto &i : ed){
		disj.uni(i.s, i.e);
		if(disj.find(s) == disj.find(e)){
			cout << i.x << endl;
			break;
		}
	}
}
int main(){
	int tc; scanf("%d",&tc);
	for(int i = 1; i <= tc; i++){
	//	printf("Case #%d: ", i);
		solve();
	}
}

