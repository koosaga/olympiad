#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

int n;
vector<int> gph[MAXN];
vector<int> v[MAXN];
int sz[MAXN], msz[MAXN];
int dap[MAXN], par[20][MAXN], dep[MAXN];

void dfs(int x, int p){
	sz[x] = 1; msz[x] = 0;
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
			sz[x] += sz[i];
			msz[x] = max(msz[x], sz[i]);
		}
	}
}

int get_center(){
	dfs(1, 0);
	pi ret(1e9, -1);
	for(int i = 1; i <= n; i++){
		int s = max(n - sz[i], msz[i]);
		ret = min(ret, pi(s, i));
	}
	return ret.second;
}

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i = 0; dx; i++){
		if(dx & 1) y = par[i][y];
		dx >>= 1;
	}
	if(x == y) return x;
	for(int i = 16; i >= 0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	return par[0][x];
}

int dist(int x, int y){
	return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

bool cmp(pi a, pi b){
	return dist(a.first, a.second) < dist(b.first, b.second);
}

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int c = get_center();
	dfs(c, -1);
	for(int i = 1; i < 20; i++){
		for(int j = 1; j <= n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i = 1; i <= n; i++){
		if(i == c) continue;
		v[sz[i]].push_back(i);
	}
	pi cur(c, c);
	for(int i = n / 2; i >= 0; i--){
		for(auto &z : v[i]){
			int x = cur.first;
			int y = cur.second;
			cur = max(cur, pi(x, z), cmp);
			cur = max(cur, pi(y, z), cmp);
		}
		dap[i*2] = dist(cur.first, cur.second);
	}
	for(int i = 1; i <= n; i++) printf("%d\n", dap[i] + 1); 
}
