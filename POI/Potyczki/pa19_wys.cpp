#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500050;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

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

struct bit{
	mint tree[MAXN];
	void clear(int l){
		fill(tree, tree + l + 1, mint(0));
	}
	void add(int x, mint v){
		x += 2;
		for(int i=x; i<MAXN; i+=i&-i) tree[i] += v;
	}
	mint query(int x){
		x += 2;
		mint ret = 0;
		for(int i=x; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit;

vector<pi> in[MAXN];
int foo[MAXN];
vector<int> ind[MAXN];

mint solve(vector<pi> v, int m){
	if(sz(v) == 0) return mint(0);
	auto flip = [&](){
		for(auto &[x, y] : v){
			tie(x, y) = pi(m-1-y, m-1-x);
		}
	};
	for(int j=0; j<=m+4; j++){
		ind[j].clear();
		foo[j] = 0;
	}
	pi ret(1e9, 1e9);
	for(int i = 0; i < 2; i++){
		for(int j=0; j<=m; j++) in[j].clear();
		for(auto &[x, y] : v){
			if(x <= y){
				in[x].emplace_back(+1, x);
				in[y+1].emplace_back(-1, x);
			}
			else{
				in[x].emplace_back(+1, x);
				in[m].emplace_back(-1, x);
				in[0].emplace_back(+1, x);
				in[y+1].emplace_back(-1, x);
			}
		}
		int cnt = 0;
		for(int j=0; j<=m; j++){
			for(auto &[x, y] : in[j]){
				if(foo[y]) cnt--;
				foo[y] += x;
				if(foo[y]) cnt++;
			}
			if(j < m) ret = min(ret, pi(cnt, 2*m*i + j));
		}
		flip();
	}
	if(ret.second >= 2*m) flip();
	
	int offset = m - 1 - ret.second % m;
	for(auto &[x, y] : v){
		x += offset;
		y += offset;
		x %= m;
		y %= m;
		if(x > y){
			ind[x].push_back(y);
		}
	}
	sort(all(v));
	ind[m].push_back(-1);
	{
		mint ret = 0;
		for(int j = m; j >= 0; j--){
			if(sz(ind[j]) == 0) continue;
			int cntFull = 0;
			sort(all(ind[j]));
			vector<pi> intervals;
			for(int k = sz(v) - 1; k >= 0; k--){
				if(v[k].first > v[k].second){
					if(v[k].first >= j) continue;
					if(j == m) continue;
					intervals.emplace_back(v[k].first, j - 1);
				}
				else{
					if(v[k].first >= j) cntFull++;
					else intervals.push_back(v[k]);
				}
			}
			vector<mint> dp(m + 5);
			dp[j] += mint(1);
			int fixed = j;
			for(auto &[l, r] : intervals){
				while(fixed > l){
					fixed--;
					dp[fixed] = dp[fixed + 1];
				}
				mint sum = dp[l] - dp[r + 2];
				dp[l] += sum;
			}
			while(fixed > 0){
				fixed--;
				dp[fixed] = dp[fixed + 1];
			}
			for(int k = 0; k < sz(ind[j]); k++){
				ret += (dp[0] - dp[ind[j][k] + 2]) * ipow(mint(2), k + cntFull);
			}
		}
		return ret;
	}
}

struct strongly_connected{
	vector<vector<int>> gph;
	 
	void init(int n){
		gph.clear();
		gph.resize(n);
	}
 
	void add_edge(int s, int e){
		gph[s].push_back(e);
	}
 
	vector<int> val, comp, z, cont;
	int Time, ncomps;
	template<class G, class F> int dfs(int j, G& g, F f) {
		int low = val[j] = ++Time, x; z.push_back(j);
		for(auto e : g[j]) if (comp[e] < 0)
			low = min(low, val[e] ?: dfs(e,g,f));
 
		if (low == val[j]) {
			do {
				x = z.back(); z.pop_back();
				comp[x] = ncomps;
				cont.push_back(x);
			} while (x != j);
			f(cont); cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	template<class G, class F> void scc(G& g, F f) {
		int n = sz(g);
		val.assign(n, 0); comp.assign(n, -1);
		Time = ncomps = 0;
		for(int i=0; i<n; i++) if (comp[i] < 0) dfs(i, g, f);
	}
 
	int piv;
	void get_scc(int n){
		scc(gph, [&](vector<int> &v){});
		for(int i=0; i<n; i++){
			comp[i] = ncomps - comp[i];
		}
		piv = ncomps; 
	}
}scc;

int n, m, a, b;
vector<int> vtx[MAXN], gph[MAXN];
pi dp[MAXN];

pi merge(vector<pi> &v){
	map<int, int> cnt;
	for(auto &[x, y] : v){
		if(x == -1) continue;
		if(x <= y){
			cnt[x]++;
			cnt[y + 1]--;
		}
		else{
			cnt[x]++;
			cnt[a]--;
			cnt[0]++;
			cnt[y+1]--;
		}
	}
	vector<pi> stk;
	int prv = 0;
	int pcnt = 0;
	for(auto &i : cnt){
		if(pcnt){
			if(sz(stk) && stk.back().second + 1 == prv){
				stk.back().second = i.first - 1;
			}
			else stk.emplace_back(prv, i.first - 1);
		}
		prv = i.first;
		pcnt += i.second;
	}
	assert(sz(stk) <= 2);
	if(sz(stk) == 0) return pi(-1, -1);
	if(sz(stk) == 1) return stk[0];
	assert(stk[0].first == 0);
	assert(stk[1].second == a - 1);
	return pi(stk[1].first, stk[0].second);
}

int main(){
	scanf("%d %d %d %d",&n,&m,&a,&b);
	scc.init(n);
	vector<pi> v;
	for(int i=0; i<m; i++){
		static char buf[69];
		int a, b;
		scanf("%d %s %d",&a,buf,&b);
		a--; b--;
		v.emplace_back(a, b);
		if(buf[1] == '-'){
			v.emplace_back(b, a);
		}
	}
	for(auto &[x, y] : v) scc.add_edge(x, y);
	scc.get_scc(n);
	for(int i=0; i<n; i++){
		vtx[scc.comp[i]].push_back(i);
	}
	for(auto &[x, y] : v){
		if(scc.comp[x] == scc.comp[y]) continue;
		gph[scc.comp[y]].push_back(scc.comp[x]);
	}
	for(int i=1; i<=scc.piv; i++){
		vector<pi> v;
		for(auto &j : gph[i]){
			v.emplace_back(dp[j]);
		}
		for(auto &j : vtx[i]){
			if(j < a) v.emplace_back(j, j);
		}
		dp[i] = merge(v);
	}
	vector<pi> solver;
	int cntEmpty = 0;
	int cntFull = 0;
	for(int i=a; i<a+b; i++){
		int v = scc.comp[i];
		if(dp[v] == pi(-1, -1)) cntEmpty++;
		else if(dp[v] == pi(0, a - 1)) cntFull++;
		else solver.push_back(dp[v]);
	}
	mint ans = solve(solver, a);
	ans += ipow(mint(2), sz(solver) + cntFull) - ipow(mint(2), sz(solver));
	ans *= ipow(mint(2), cntEmpty);
	cout << ans << endl;
}
