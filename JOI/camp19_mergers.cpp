#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500050;
using lint = long long;
using pi = pair<int, int>;

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

int n, k;
vector<int> gph[MAXN];
vector<int> grp[MAXN];
vector<int> dfn;
int par[19][MAXN], dep[MAXN], din[MAXN];
int cnt[MAXN], dx[MAXN], piv;

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i=0; i<19; i++){
		if((dx >> i) & 1) y = par[i][y];
	}
	for(int i=18; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

void dfs(int x, int p){
	dfn.push_back(x);
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		grp[x].push_back(i);
	}
	dfs(1, 0);
	for(int i=1; i<19; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i=1; i<=k; i++){
		sort(grp[i].begin(), grp[i].end(), [&](const int &a, const int &b){
			return din[a] < din[b];
		});
		for(int j=0; j+1<grp[i].size(); j++){
			int ps = grp[i][j];
			int pe = grp[i][j+1];
			dx[pe]++; dx[ps]++; dx[lca(ps, pe)] -= 2;
		}
	}
	disj.init(n);
	for(int i=dfn.size()-1; i>=0; i--){
		int x = dfn[i];
		for(auto &j : gph[x]){
			if(j != par[0][x]) dx[x] += dx[j];
		}
		if(dx[x] > 0) disj.uni(par[0][x], x);
	}
	for(int i=2; i<=n; i++){
		int l = disj.find(par[0][i]);
		int r = disj.find(i);
		if(l != r) cnt[l]++, cnt[r]++;
	}
	int sum = count(cnt + 1, cnt + n + 1, 1);
	printf("%d\n", (sum + 1) / 2);
}
