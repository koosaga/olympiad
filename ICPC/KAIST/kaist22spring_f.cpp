#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 100005;

int n;
vector<int> gph[MAXN];
int par[17][MAXN], dep[MAXN], din[MAXN], dout[MAXN], piv;

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &y : gph[x]){
		if(y != p){
			par[0][y] = x;
			dep[y] = dep[x] + 1;
			dfs(y, x);
		}
	}
	dout[x] = piv;
}

int lca(int u, int v){
	if(dep[u] > dep[v]) swap(u, v);
	int dx = dep[v] - dep[u];
	for(int i = 0; dx; i++){
		if(dx & 1){
			v = par[i][v];
		}
		dx >>= 1;
	}
	for(int i = 16; i >= 0; i--){
		if(par[i][u] != par[i][v]){
			u = par[i][u];
			v = par[i][v];
		}
	}
	if(u != v) return par[0][u];
	return u;
}

bool in(int u, int v){ return din[u] <= din[v] && dout[v] <= dout[u]; }


vector<int> vtree[MAXN];
map<int, int> mp[MAXN];
int from[MAXN], og[MAXN];

lint solve(int k){
	vector<int> v;
	for(int i = k; i <= n; i += k) v.push_back(i);
	sort(all(v), [&](const int &a, const int &b){
		return din[a] < din[b];
	});
	{
		for(auto &i : v) og[i] = 1;
	}
	{
		int m = sz(v);
		for(int i = 0; i < m - 1; i++){
			int l = lca(v[i], v[i+1]);
			v.push_back(l);
		}
	}
	sort(all(v), [&](const int &a, const int &b){
		return din[a] < din[b];
	});
	v.resize(unique(all(v)) - v.begin());
	vector<int> stk;
	for(auto &i : v){
		while(sz(stk) && !in(stk.back(), i)) stk.pop_back();
		if(sz(stk)){
			int p = stk.back();
			int v = i;
			vtree[p].emplace_back(v);
		}
		stk.push_back(i);
	}
	reverse(all(v));
	lint ret = 0;
	for(auto &i : v){
		from[i] = i;
		if(og[i]){
			mp[from[i]][dep[i] % k]++; 
		}
		for(auto &j : vtree[i]){
			if(sz(mp[from[i]]) < sz(mp[from[j]])){
				swap(from[i], from[j]);
			}
			for(auto &[key, val] : mp[from[j]]){
				int newKey = (dep[i] * 2 - key + k) % k;
				auto it = mp[from[i]].find(newKey);
				if(it != mp[from[i]].end()) ret += 1ll * it->second * val;
			}
			for(auto &[key, val] : mp[from[j]]){
				mp[from[i]][key] += val;
			}
		}
	}
	// clean up
	for(auto &i : v){
		mp[i].clear();
		vtree[i].clear();
		og[i] = 0;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n-1; i++){
		int u, v; cin >> u >> v;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(1, -1);
	for(int i = 1; i < 17; i++){
		for(int j = 1; j <= n; j++) par[i][j] = par[i-1][par[i-1][j]];
	}
	vector<lint> pairs(n + 1);
	pairs[1] = 1ll * n * (n - 1) / 2; // sangsoo not confident
	for(int i = 2; i < n; i++){
		pairs[i] = solve(i);
	}
	lint ret = 0;
	for(int i = n-1; i >= 1; i--){
		for(int j = 2 * i; j < n; j += i){
			pairs[i] -= pairs[j];
		}
		ret += 1ll * pairs[i] * i;
	}
	cout << ret << "\n";
}
