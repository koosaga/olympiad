#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;
namespace tree{
	vector<int> gph[MAXN];
	int dep[MAXN];
	int par[17][MAXN];
	int up[MAXN], dn[MAXN];
	void add_edge(int s, int e){
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	vector<int> dfn;
	void dfs(int x, int p = -1){
		dfn.push_back(x);
		for(auto &i : gph[x]){
			if(i != p){
				dep[i] = dep[x] + 1;
				par[0][i] = x;
				dfs(i, x);
			}
		}
	}
	void make_ds(int n){
		dfs(1);
		for(int i=1; i<17; i++){
			for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	int lca(int x, int y){
		if(dep[x] > dep[y]) swap(x, y);
		int dx = dep[y] - dep[x];
		for(int i=0; i<17; i++){
			if((dx >> i) & 1) y = par[i][y];
		}
		for(int i=16; i>=0; i--){
			if(par[i][x] != par[i][y]){
				x = par[i][x];
				y = par[i][y];
			}
		}
		if(x != y) return par[0][x];
		return x;
	}
	void set_path(int x, int y){
		int l = lca(x, y);
		up[x] += 1;
		up[l] -= 1;
		dn[y] += 1;
		dn[l] -= 1;
	}
	bool solve(int n){
		reverse(all(dfn));
		for(auto &i : dfn){
			for(auto &j : gph[i]){
				if(j == par[0][i]) continue;
				up[i] += up[j];
				dn[i] += dn[j];
			}
			if(up[i] && dn[i]) return 0;
		}
		return 1;
	}
}

pi edg[MAXN];
vector<pi> gph[MAXN];
int n, m, dfn[MAXN], low[MAXN], dep[MAXN], piv;
int idx[MAXN];
bool bridge[MAXN];

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i.first == p) continue;
		if(!dfn[i.second]){
			dep[i.second] = dep[x] + 1;
			dfs(i.second, i.first);
			if(low[i.second] > dfn[x]){
				bridge[i.first] = 1;
			}
			low[x] = min(low[x], low[i.second]);
		}
		else low[x] = min(low[x], dfn[i.second]);
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		edg[i] = pi(s, e);
		gph[s].emplace_back(i, e);
		gph[e].emplace_back(i, s);
	}
	dfs(1, -1);
	disj.init(n);
	for(int i=0; i<m; i++){
		if(!bridge[i]){
			disj.uni(edg[i].first, edg[i].second);
		}
	}
	piv = 0;
	for(int i=1; i<=n; i++){
		if(disj.find(i) == i) idx[i] = ++piv;
	}
	for(int i=0; i<m; i++){
		if(bridge[i]){
			int l = disj.find(edg[i].first);
			int r = disj.find(edg[i].second);
			l = idx[l];
			r = idx[r];
			tree::add_edge(l, r);
		}
	}
	tree::make_ds(piv);
	int q; scanf("%d",&q);
	while(q--){
		int x, y; scanf("%d %d",&x,&y);
		x = disj.find(x);
		y = disj.find(y);
		x = idx[x], y = idx[y];
		if(x != y){
			tree::set_path(x, y);
		}
	}
	if(!tree::solve(piv)){
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=0; i<m; i++){
		int x = edg[i].first;
		int y = edg[i].second;
		if(!bridge[i]){
			if(dep[x] > dep[y]) swap(x, y);
			if(dep[x] + 1 == dep[y]) printf("%d %d\n", x, y);
			else printf("%d %d\n", y, x);
		}
		else{
			int l = idx[disj.find(x)];
			int r = idx[disj.find(y)];
			if(tree::dep[l] < tree::dep[r]) swap(l, r), swap(x, y);
			assert(tree::dep[l] - 1 == tree::dep[r]);
			if(tree::up[l]) printf("%d %d\n", x, y);
			else printf("%d %d\n", y, x);
		}
	}
}
