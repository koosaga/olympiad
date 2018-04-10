#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
typedef pair<int, int> pi;

int n, q;
int par[17][MAXN], dep[MAXN];
int nxt[MAXN], cost[MAXN];
vector<int> gph[MAXN];

int up(int s, int e, int x){
	if(dep[s] <= dep[e]) return s;
	if(nxt[s] != s) return nxt[s] = up(nxt[s], e, x);
	cost[s] = x;
	return nxt[s] = up(par[0][s], e, x);
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

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

vector<pi> ed_input;
int main(){
	freopen("disrupt.in", "r", stdin);
	freopen("disrupt.out", "w", stdout);
	scanf("%d %d",&n,&q);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		ed_input.emplace_back(s, e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
	}
	iota(nxt, nxt + n + 1, 0);
	memset(cost, -1, sizeof(cost));
	vector<tuple<int, int, int>> w;
	for(int i=0; i<q; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		w.emplace_back(x, s, e);
	}
	sort(w.begin(), w.end());
	for(auto &i : w){
		int s, e, x;
		tie(x, s, e) = i;
		int l = lca(s, e);
		up(s, l, x);
		up(e, l, x);
	}
	for(auto &i : ed_input){
		if(dep[i.first] > dep[i.second]){
			swap(i.first, i.second);
		}
		printf("%d\n", cost[i.second]);
	}
}
