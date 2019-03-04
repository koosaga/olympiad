#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n, dep[200005], par[18][200005];
vector<int> gph[200005];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i=0; i<18; i++){
		if((dx >> i) & 1) y = par[i][y];
	}
	for(int i=17; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	lint ans = 0;
	for(int i=1; i<=n; i++){
		for(int j=2*i; j<=n; j+=i) ans += 1 + dep[i] + dep[j] - 2 * dep[lca(i, j)];
	}
	cout << ans;
}
