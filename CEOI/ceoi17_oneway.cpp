#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
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
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

vector<pi> gph[MAXN], tr[MAXN];
int n, m, s[MAXN], e[MAXN];
int dfn[MAXN], low[MAXN], comp[MAXN], piv, ccnt;
int chkl[MAXN], chkr[MAXN];

void dfs(int x, int pe){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(pe == i.first) continue;
		if(!dfn[i.second]){
			dfs(i.second, i.first);
			low[x] = min(low[x], low[i.second]);
		}
		else{
			low[x] = min(low[x], dfn[i.second]);
		}
	}	
}

void dcmp(int x, int c){
	comp[x] = c;
	for(auto &i : gph[x]){
		if(comp[i.second]) continue;
		if(low[i.second] > dfn[x]) dcmp(i.second, ++ccnt);
		else dcmp(i.second, c);
	}
}

int dep[MAXN], par[17][MAXN], pe[MAXN];
int up[MAXN], dn[MAXN];

void dfs2(int x, int p){
	for(auto &i : tr[x]){
		if(i.second == p) continue;
		pe[i.second] = i.first;
		par[0][i.second] = x;
		dep[i.second] = dep[x] + 1;
		dfs2(i.second, x);
	}
}

void dfs3(int x, int p){
	for(auto &i : tr[x]){
		if(i.second == p) continue;
		dfs3(i.second, x);
		up[x] += up[i.second];
		dn[x] += dn[i.second];
	}
}

int getlca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) s = par[i][s];
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

void direct(int st, int ed, int idx){
	if(pi(st, ed) != pi(comp[s[idx]], comp[e[idx]])) chkr[idx] = 1;
	else chkl[idx] = 1;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		if(s[i] == e[i]){
			continue;
		}
		gph[s[i]].push_back(pi(i, e[i]));
		gph[e[i]].push_back(pi(i, s[i]));
	}
	for(int i=1; i<=n; i++){
		if(!dfn[i]){
			dfs(i, -1);
			dcmp(i, ++ccnt);
		}
	}
	disj.init(ccnt);
	for(int i=0; i<m; i++){
		if(comp[s[i]] != comp[e[i]]){
			int st = comp[s[i]];
			int ed = comp[e[i]];
			disj.uni(st, ed);
			tr[st].push_back(pi(i, ed));
			tr[ed].push_back(pi(i, st));
		}
	}
	for(int i=2; i<=ccnt; i++){
		if(disj.uni(1, i)){
			tr[1].push_back(pi(-1, i));
			tr[i].push_back(pi(-1, 1));
		}
	}
	dfs2(1, -1);
	for(int i=1; i<17; i++){
		for(int j=1; j<=ccnt; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	int q;
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		s = comp[s];
		e = comp[e];
		int l = getlca(s, e);
		up[s]++;
		up[l]--;
		dn[e]++;
		dn[l]--;
	}
	dfs3(1, 0);
	for(int i=2; i<=ccnt; i++){
		if(up[i]) direct(i, par[0][i], pe[i]);
		else if(dn[i]) direct(par[0][i], i, pe[i]);

	}
	for(int i=0; i<m; i++){
		if(chkr[i]) putchar('L');
		else if(chkl[i]) putchar('R');
		else putchar('B');
	}
}
