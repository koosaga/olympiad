#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 200005;
const int MAXT = 530000;

namespace gugugu{
	struct path{
		int cost, s, e;
	};

	int n, m;
	vector<int> gph[MAXN];
	vector<path> paths[MAXN];
	int par[MAXN][18], dep[MAXN];

	int dfn[MAXN], sz[MAXN], p0, tra[MAXN];
	int comp[MAXN], cnum[MAXN], chead[MAXN], csize[MAXN], piv;
	int son[MAXN];

	int lca(int x, int y){
		if(dep[x] > dep[y]) swap(x,y);
		int diff = dep[y] - dep[x];
		for (int i=0; i<18; i++) {
			if((diff >> i) & 1) y = par[y][i];
		}
		for (int i=17; i>=0; i--) {
			if(par[x][i] != par[y][i]){
				x = par[x][i];
				y = par[y][i];
			}
		}
		if(x == y) return x;
		return par[x][0];
	}

	void dfs(int pos, int pa){
		dfn[pos] = ++p0;
		tra[dfn[pos]] = pos;
		par[pos][0] = pa;
		dep[pos] = dep[pa] + 1;
		for (int i=1; i<18; i++) {
			par[pos][i] = par[par[pos][i-1]][i-1];
		}
		for (auto &x : gph[pos]){
			if(x == pa) continue;
			dfs(x,pos);
			sz[pos] += sz[x];
		}
		sz[pos]++;
	}

	void hld(int pos){
		comp[pos] = piv;
		cnum[pos] = ++csize[piv];
		int pmax = -1, vmax = -1;
		for (int i=0; i<gph[pos].size(); i++) {
			if(gph[pos][i] == par[pos][0]) continue;
			if(vmax < sz[gph[pos][i]]){
				vmax = sz[gph[pos][i]];
				pmax = i;
			}
		}
		if(pmax == -1) return;
		son[pos] = gph[pos][pmax];
		hld(gph[pos][pmax]);
		for (int i=0; i<gph[pos].size(); i++) {
			if(gph[pos][i] == par[pos][0] || i == pmax) continue;
			piv++;
			chead[piv] = gph[pos][i];
			hld(gph[pos][i]);
		}
	}

	lint dp[MAXN], sum[MAXN];
	lint mark[MAXN];
	vector<lint> psum[MAXN];

	lint getsum(int num, int s, int e){
		if(s > e) return 0;
		return psum[num][s] - psum[num][e+1];
	}

	lint f(int x, int y, int l){
		lint ret = 0;
		while (comp[x] != comp[l]) {
			ret += getsum(comp[x],1,cnum[x]);
			x = par[chead[comp[x]]][0];
		}
		ret += getsum(comp[l],cnum[l]+1,cnum[x]);
		while (comp[y] != comp[l]) {
			ret += getsum(comp[y],1,cnum[y]);
			y = par[chead[comp[y]]][0];
		}
		ret += getsum(comp[l],cnum[l]+1,cnum[y]);
		ret += sum[l];
		return ret;
	}

	void solve(){
		for (int i=n; i; i--) {
			lint pos = tra[i];
			for (auto &j : gph[pos]){
				if(j == par[pos][0]) continue;
				sum[pos] += dp[j];
			}
			lint ret = sum[pos];
			for (auto &j : paths[pos]){
				ret = max(ret,f(j.s,j.e,pos) + j.cost);
			}
			dp[pos] = ret;
			ret = sum[pos] - dp[pos];
			psum[comp[pos]][cnum[pos]] = psum[comp[pos]][cnum[pos]+1] + ret;
		}
	}

	void init(int _n, int _m){
		n = _n; m = _m;
	}
	void add_edge(int x, int y){
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	void proc1(){
		dfs(1, 0);
	}
	void add_path(int x, int y, int c){
		int l = lca(x,y);
		paths[l].push_back({c,x,y});
	}
	lint proc2(){
		piv = 1;
		hld(1);
		for (int i=1; i<=piv; i++) {
			psum[i].resize(csize[i] + 2);
		}
		solve();
		return dp[1];
	}
}

struct seg{
	int lim;
	pi tree[MAXT];
	void init(int n, int *a = NULL){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(-1e9, 1e9));
		if(a) for(int i=1; i<=n; i++) tree[i + lim] = pi(a[i], i);
		for(int i=lim; i>0; i--){
			tree[i] = max(tree[2*i], tree[2*i+1]);
		}
	}
	void upd(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

struct star{
	int x, y, val, st, ed;
	bool operator<(const star &s)const{
		return x < s.x;
	}
}b[MAXN];

int n, m, a[MAXN];
int piv, danmal[MAXN];

void solve(int s, int e, int x, int p){
	if(s > e) return;
	piv++;
	auto k = seg1.query(s, e);
	danmal[k.second] = piv;
	if(p) gugugu::add_edge(p, piv);
	int lo = lower_bound(b + 1, b + m + 1, (star){s, -1, -1}) - b;
	int hi = upper_bound(b + 1, b + m + 1, (star){e, -1, -1}) - b - 1;
	while(true){
		auto qr = seg2.query(lo, hi);
		if(qr.first <= k.first) break;
		b[qr.second].st = piv;
		seg2.upd(qr.second, pi(-1e9, -1e9));
	}
	solve(s, k.second - 1, k.first, danmal[k.second]);
	solve(k.second + 1, e, k.first, danmal[k.second]);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	gugugu::init(n, m);
	scanf("%d",&m);
	for(int i=1; i<=m; i++) scanf("%d %d %d",&b[i].x,&b[i].y,&b[i].val);
	sort(b + 1, b + m + 1);
	seg1.init(n, a);
	seg2.init(m);
	lint sum = 0;
	for(int i=1; i<=m; i++){
		sum += b[i].val;
		seg2.upd(i, pi(b[i].y, i));
	}
	solve(1, n, 1e9, 0);
	for(int i=1; i<=m; i++) b[i].ed = danmal[b[i].x];
	gugugu::proc1();
	for(int i=1; i<=m; i++) gugugu::add_path(b[i].st, b[i].ed, b[i].val);
	printf("%lld\n", sum - gugugu::proc2());
}
