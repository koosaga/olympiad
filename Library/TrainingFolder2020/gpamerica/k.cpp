#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;

int n, q;
vector<int> gph[MAXN];
int par[19][MAXN], dep[MAXN];

int lca(int x, int y){
	if(dep[x] < dep[y]) swap(x, y);
	int ret = dep[x] - dep[y];
	for(int i=0; i<19; i++){
		if(ret & (1<<i)) x = par[i][x];
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

int dis(int x, int y){
	return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}
void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<19; i++){
		for(int j=1; j<=n; j++){
			par[i][j]  = par[i-1][par[i-1][j]];
		}
	}
	while(q--){
		int x, y; scanf("%d %d",&x,&y);
		int d = dis(x, y);
		printf("%lld\n", n + 1ll * d * (d + 1) / 2);
	}
}
