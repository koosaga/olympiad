#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
using pi = pair<int, int>;
using lint = long long;

struct disj{
	int pa[MAXN], sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 1);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
	int getsz(int x){ return sz[find(x)]; }
}disj;

int n, c;
vector<int> gph[MAXN];
vector<int> bcc[MAXN], cmp[MAXN];
int dfn[MAXN], low[MAXN], sz[MAXN], piv;

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(!dfn[i]){
			dfs(i, x);
			sz[x] += sz[i];
			low[x] = min(low[x], low[i]);
		}
		else low[x] = min(low[x], dfn[i]);
	}
}

void color(int x, int p){
	if(p){
		bcc[p].push_back(x);
		cmp[x].push_back(p);
	}
	for(auto &i : gph[x]){
		if(cmp[i].size()) continue;
		if(low[i] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i, c);
		}
		else color(i, p);
	}
}

int main(){
	int m;
	scanf("%d %d",&n,&m);
	while(m--){
		int t, prv;
		scanf("%d %d",&t,&prv);
		for(int j=0; j<t-1; j++){
			int cur; scanf("%d",&cur);
			gph[prv].push_back(cur);
			gph[cur].push_back(prv);
			prv = cur;
		}
	}
	dfs(1, 0);
	color(1, 0);
	disj.init(n);
	lint ret = 0;
	for(int i=1; i<=c; i++){
		if(bcc[i].size() == 2){
			disj.uni(bcc[i][0], bcc[i][1]);
			int s = sz[bcc[i][1]];
			ret += 1ll * (n - s) * s - 1;
		}
	}
	lint actual_sums = 0;
	for(int i=1; i<=n; i++){
		if(disj.find(i) == i){
			actual_sums += 1ll * (disj.sz[i] - 1) * (disj.sz[i] - 2) / 2;
		}
	}
	for(int i=1; i<=c; i++){
		if(bcc[i].size() == 2) continue;
		lint cur_sums = actual_sums;
		int subsz = 0;
		for(auto &j : bcc[i]){
			cur_sums -= 1ll * (disj.getsz(j) - 1) * (disj.getsz(j) - 2) / 2;
			subsz += disj.getsz(j);
		}
		cur_sums += 1ll * (subsz - 1) * (subsz - 2) / 2;
		ret += bcc[i].size() * (cur_sums - 1);
	}
	cout << ret << endl;
}
