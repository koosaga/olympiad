#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 500010;

namespace dtree{
	vector <int> E[MAXN];
	vector <int> RE[MAXN], rdom[MAXN];

	int S[MAXN], RS[MAXN], cs;
	int par[MAXN], val[MAXN];
	int sdom[MAXN], rp[MAXN];
	int dom[MAXN];

	void clear(int n) {
		cs = 0;
		for(int i=0;i<=n;i++) {
			par[i] = val[i] = sdom[i] = rp[i] = dom[i] = S[i] = RS[i] = 0;
			E[i].clear(); RE[i].clear(); rdom[i].clear();
		}
	}

	void addE(int x, int y) {
		E[x].push_back(y);
	}

	int Find(int x, int c = 0) {
		if(par[x] == x) return c ? -1 : x;
		int p = Find(par[x], 1);
		if(p == -1) return c ? par[x] : val[x];
		if(sdom[val[x]] > sdom[val[par[x]]]) val[x] = val[par[x]];
		par[x] = p;
		return c ? p : val[x];
	}

	void Union(int x, int y) {
		par[x] = y;
	}

	void dfs(int x) {
		RS[ S[x] = ++cs ] = x;
		par[cs] = sdom[cs] = val[cs] = cs;
		for(int e : E[x]) {
			if(S[e] == 0) dfs(e), rp[S[e]] = S[x];
			RE[S[e]].push_back(S[x]);
		}
	}

	int solve(int s, int *up) { // Calculate idoms
		dfs(s);
		for(int i=cs;i;i--) {
			for(int e : RE[i]) sdom[i] = min(sdom[i], sdom[Find(e)]);
			if(i > 1) rdom[sdom[i]].push_back(i);
			for(int e : rdom[i]) {
				int p = Find(e);
				if(sdom[p] == i) dom[e] = i;
				else dom[e] = p;
			}
			if(i > 1) Union(i, rp[i]);
		}
		for(int i=2;i<=cs;i++) if(sdom[i] != dom[i]) dom[i] = dom[dom[i]];
		for(int i=2;i<=cs;i++) {
			up[RS[i]] = RS[dom[i]];
		}
		return cs;
	}
};

vector<int> gph[MAXN];
int par[MAXN], sz[MAXN];
int s[MAXN], e[MAXN];


void dfs(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		dfs(i);
		sz[x] += sz[i];
	}
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		dtree::addE(s[i], e[i]);
	}
	dtree::solve(1, par);
	for(int i=2; i<=n; i++){
		if(par[i]) gph[par[i]].push_back(i);
	}
	dfs(1);
	lint ans = 1ll * n * (n-1);
	for(auto &i : gph[1]) ans -= 1ll * sz[i] * (sz[i] - 1);
	cout << (ans / 2);
}
