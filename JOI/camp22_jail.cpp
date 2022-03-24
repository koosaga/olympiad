#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 120005;

vector<vector<int>> gph;
int par[17][MAXN], dep[MAXN];

void dfs(int x, int p){
	for(auto &y : gph[x]){
		if(y != p){
			par[0][y] = x;
			dep[y] = dep[x] + 1;
			dfs(y, x);
		}
	}
}

struct digraph{
	vector<int> gph[36 * MAXN];
	int deg[36 * MAXN];
	void add_edge(int s, int e){
		gph[s].push_back(e);
		deg[e]++;
	}
	void init(int n){
		for(int i = 0; i < n; i++){
			gph[i].clear();
			deg[i] = 0;
		}
	}
	bool query(int n){
		queue<int> que;
		for(int i = 0; i < n; i++){
			if(deg[i] == 0) que.push(i);
		}
		while(sz(que)){
			int x = que.front();
			que.pop();
			for(auto &y : gph[x]){
				deg[y]--;
				if(deg[y] == 0) que.push(y);
			}
		}
		if(*max_element(deg, deg + n)) return 0;
		return 1;
	}
}dg;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q; cin >> q;
	while(q--){
		int n; cin >> n;
		gph.clear();
		gph.resize(n + 1);
		for(int i = 0; i < n - 1; i++){
			int s, e; cin >> s >> e;
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		dfs(1, -1);
		for(int i = 1; i < 17; i++){
			for(int j = 1; j <= n; j++){
				par[i][j] = par[i-1][par[i-1][j]];
			}
		}
		int m; cin >> m;
		vector<pi> a(m);
		auto startIdx = [&](int i, int j){
			return (i + 1) * n + j - 1;
		};
		auto endIdx = [&](int i, int j){
			return (i + 18) * n + j - 1;
		};
		dg.init(36 * n);
		vector<int> starts(n+1, -1), ends(n+1, -1);
		for(int i = 0; i < m; i++){
			int s, e; cin >> s >> e;
			a[i] = pi(s, e);
			starts[s] = i;
			ends[e] = i;
			dg.add_edge(startIdx(0, s), i);
			dg.add_edge(i, endIdx(0, e));
		}
		auto lca = [&](int s, int e){
			if(dep[s] > dep[e]) swap(s, e);
			int dx = dep[e] - dep[s];
			for(int i = 0; dx; i++){
				if(dx & 1){
					e = par[i][e];
				}
				dx >>= 1;
			};
			for(int i = 16; i >= 0; i--){
				if(par[i][s] != par[i][e]){
					s = par[i][s];
					e = par[i][e];
				}
			}
			if(s != e) return par[0][s];
			return s;
		};
		auto anc = [&](int e, int dx){
			for(int i = 0; dx; i++){
				if(dx & 1){
					e = par[i][e];
				}
				dx >>= 1;
			}
			return e;
		};
		for(int i = 1; i < 17; i++){
			for(int j = 1; j <= n; j++){
				if(dep[j] >= (1 << i) - 1){
					dg.add_edge(startIdx(i, j), startIdx(i - 1, j));
					dg.add_edge(startIdx(i, j), startIdx(i - 1, par[i-1][j]));
					dg.add_edge(endIdx(i - 1, j), endIdx(i, j));
					dg.add_edge(endIdx(i - 1, par[i-1][j]), endIdx(i, j));
				}
			}
		}
		for(int i = 0; i < m; i++){
			int s = a[i].first;
			int e = a[i].second;
			int l = lca(s, e);
			auto addEdge = [&](int v, int l){
				if(l <= 0) return;
				int it = 0;
				while((2 << it) <= l) it++;
				int w = anc(v, l - (1<<it));
				dg.add_edge(i, startIdx(it, v));
				dg.add_edge(i, startIdx(it, w));
				dg.add_edge(endIdx(it, v), i);
				dg.add_edge(endIdx(it, w), i);
			};
			addEdge(par[0][s], dep[s] - dep[l] - 1);
			addEdge(par[0][e], dep[e] - dep[l] - 1);
			dg.add_edge(endIdx(0, s), i);
			dg.add_edge(i, startIdx(0, e));
			if(~starts[l] && starts[l] != i) dg.add_edge(i, startIdx(0, l));
			if(~ends[l] && ends[l] != i) dg.add_edge(endIdx(0, l), i);
		}
		cout << (dg.query(36*n) ? "Yes" : "No") << "\n";
	}
}
