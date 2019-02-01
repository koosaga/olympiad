#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int par[20][1000005], dep[1000005];
vector<int> gph[1000005];
int n, s, q;

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i == p) continue;
		dep[i] = dep[x] + 1;
		par[0][i] = x;
		dfs(i, x);
	}
}

int lca(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int dx = dep[u] - dep[v];
	for(int i=0; i<20; i++){
		if((dx >> i) & 1) u = par[i][u];
	}
	for(int i=19; i>=0; i--){
		if(par[i][u] != par[i][v]){
			u = par[i][u];
			v = par[i][v];
		}
	}
	if(u != v) return par[0][v];
	return v;
}

int main(){
	cin >> n >> s >> q;
	for(int i=0; i<n-1; i++){
		int u, v;
		scanf("%d %d",&u,&v);
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(1, 0);
	for(int i=1; i<20; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	while(q--){
		int d, t;
		scanf("%d %d",&d,&t);
		int l = lca(s, d);
		if(dep[s] + dep[d] - 2 * dep[l] <= t){
			s = d;
		}
		else if(dep[s] - dep[l] <= t){
			int v = dep[s] + dep[d] - 2 * dep[l] - t;
			for(int i=0; i<20; i++){
				if((v >> i) & 1) d = par[i][d];
			}
			s = d;
		}
		else{
			for(int i=0; i<20; i++){
				if((t >> i) & 1) s = par[i][s];
			}
		}
		printf("%d ", s);
	}
}
