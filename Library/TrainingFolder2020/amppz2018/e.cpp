#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int MAXM = 1000005;

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
	int s, e, x, idx;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
}e[MAXM];

int n, m;
int is_in[MAXM], ans[MAXM];
int par[17][MAXN], pae[17][MAXN], dep[MAXN];
vector<pi> gph[MAXN];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i.second != p){
			par[0][i.second] = x;
			pae[0][i.second] = i.first;
			dep[i.second] = dep[x] + 1;
			dfs(i.second, x);
		}
	}
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int path_max(int p, int l){
	int dx = dep[p] - dep[l];
	int ret = 0;
	for(int i=0; i<17; i++){
		if((dx >> i) & 1){
			ret = max(ret, pae[i][p]);
			p = par[i][p];
		}
	}
	return ret;
}

int pa[MAXN], pval[MAXN];

int paint(int s, int l, int v){
	if(pa[s] != s) return pa[s] = paint(pa[s], l, v);
	if(dep[s] <= dep[l]) return s;
	pval[s] = min(pval[s], v);
	return pa[s] = paint(par[0][s], l, v);
}

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&e[i].s,&e[i].e,&e[i].x);
		e[i].idx = i;
	}
	sort(e, e + m);
	for(int i=0; i<m; i++){
		if(disj.uni(e[i].s, e[i].e)){
			gph[e[i].s].emplace_back(e[i].x, e[i].e);
			gph[e[i].e].emplace_back(e[i].x, e[i].s);
			is_in[i] = 1;
		}
	}
	dfs(1, 0);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
			pae[i][j] = max(pae[i-1][j], pae[i-1][par[i-1][j]]);
		}
	}
	fill(pval + 2, pval + n + 1, 1000000000);
	iota(pa, pa + n + 1, 0);
	for(int i=0; i<m; i++){
		if(!is_in[i]){
			int l = lca(e[i].s, e[i].e);
			ans[e[i].idx] = max(path_max(e[i].s, l), path_max(e[i].e, l));
			paint(e[i].s, l, e[i].x);
			paint(e[i].e, l, e[i].x);
		}
	}
	for(int i=0; i<m; i++){
		if(is_in[i]){
			if(par[0][e[i].s] == e[i].e) swap(e[i].s, e[i].e);
			ans[e[i].idx] = pval[e[i].e];
		}
	}
	for(int i=0; i<m; i++) printf("%d\n", ans[i]);
}
