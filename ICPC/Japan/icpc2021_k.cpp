#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 100005;

vector<int> indeg;
vector<vector<int>> gph;
vector<int> vis, instk, cyc, par;

void dfs(int x){
	vis[x] = 1;
	instk[x] = 1;
	for(auto &y : gph[x]){
		if(!vis[y]){
			par[y] = x;
			dfs(y);
		}
		else if(instk[y] && !sz(cyc)){
			for(int j = x; j != y; j = par[j]){
				cyc.push_back(j);
			}
			cyc.push_back(y);
			reverse(all(cyc));
		}
	}
	instk[x] = 0;
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m; cin >> n >> m;
	if(n >= m){
		for(int i = 0; i < m; i++) cout << i + 1 << " ";
		return 0;
	}
	vector<vector<int>> v(n, vector<int>(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> v[i][j];
		}
	}
	vector<vector<int>> iset(n);
	vector<int> assign(n);
	vector<vector<lint>> cost(n, vector<lint>(n));
	for(int i = 0; i < n; i++){
		iset[i].push_back(i);
		assign[i] = i;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(auto &k : iset[j]) cost[i][j] += v[i][k];
		}
	}
	vis.resize(n);
	instk.resize(n);
	gph.resize(n);
	par.resize(n);
	for(int i = n; i < m; i++){
		while(true){
			vector<int> indeg(n);
			for(int j = 0; j < n; j++){
				for(int k = 0; k < n; k++){
					if(cost[j][assign[j]] < cost[j][assign[k]]){
						indeg[k]++;
					}
				}
			}
			bool ok = 0;
			for(int j = 0; j < n; j++){
				if(indeg[j] == 0){
					iset[assign[j]].push_back(i);
					for(int k = 0; k < n; k++) cost[k][assign[j]] += v[k][i];
					ok = 1;
					break;
				}
			}
			if(ok) break;
			for(int j = 0; j < n; j++){
				for(int k = 0; k < n; k++){
					if(cost[j][assign[j]] < cost[j][assign[k]]){
						gph[j].push_back(k);
					}
				}
			}
			for(int j = 0; j < n; j++){
				if(!vis[j]){
					dfs(j);
					if(sz(cyc)){
						vector<int> idx;
						for(int k = 0; k < sz(cyc); k++) idx.push_back(assign[cyc[k]]);
						for(int k = 0; k < sz(cyc); k++) assign[cyc[k]] = idx[(k + 1) % sz(cyc)];
						cyc.clear();
						break;
					}
				}
			}
			for(int j = 0; j < n; j++) gph[j].clear(), vis[j] = 0;
		}
	}
	vector<int> ans(m);
	for(int i = 0; i < n; i++){
		for(auto &j : iset[assign[i]]) ans[j] = i + 1;
	}
	for(auto &x : ans) cout << x << " ";
}
