#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
const int mod = 1e9 + 7;

int par[MAXN], dep[MAXN], sz[MAXN];
vector<int> gph[MAXN];

void dfs(int x, int p){
	sz[x] = 1;
	for(auto &y : gph[x]){
		if(y != p){
			par[y] = x;
			dep[y] = dep[x] + 1;
			dfs(y, x);
			sz[x] += sz[y];
		}
	}
}

int lca(int x, int y){
	while(dep[x] < dep[y]) y = par[y];
	while(dep[x] > dep[y]) x = par[x];
	while(x != y) x = par[x], y = par[y];
	return x;
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, q; cin >> n >> q;
	for(int i = 0; i < n - 1; i++){
		int s, t; cin >> s >> t;
		gph[s].push_back(t);
		gph[t].push_back(s);
	}
	dfs(1, 0);
	while(q--){
		int u, v; cin >> u >> v;
		int l = lca(u, v);
		vector<int> seql, seqr;
		int prv = -1;
		int tot = n;
		for(int i = u; i != l; i = par[i]){
			seql.push_back(sz[i] - (prv != -1 ? sz[prv] : 0));
			prv = i;
		}
		if(prv != -1) tot -= sz[prv];
		prv = -1;
		for(int i = v; i != l; i = par[i]){
			seqr.push_back(sz[i] - (prv != -1 ? sz[prv] : 0));
			prv = i;
		}
		if(prv != -1) tot -= sz[prv];
		reverse(all(seqr));
		seql.push_back(tot);
		for(auto &x : seqr) seql.push_back(x);
		int n = sz(seql);
		lint ret = 0, sum = 0;
		for(int i = n/2+1; i < n; i++){
			sum += seql[i - n/2 - 1];
			ret += seql[i] * sum;
		}
		cout << ret << "\n";
	}
}

