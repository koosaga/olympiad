#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
 
// Dynamic shortest path on bounded treewidth, O(nk^4 log n + qk log n)

struct treeDecomp{
	bool valid;
	vector<int> par;
	vector<vector<int>> bags;
};
 
// Tree decomposition, width 2
treeDecomp tree_decomposition(int n, vector<pi> edges){
	vector<set<int>> gph(n);
	for(auto &[u, v] : edges){
		gph[u].insert(v);
		gph[v].insert(u);
	}
	treeDecomp ret;
	ret.valid = false;
	ret.par.resize(n, -1);
	ret.bags.resize(n);
	queue<int> que;
	for(int i = 0; i < n; i++){
		if(sz(gph[i]) <= 2) que.push(i);
	}
	auto rem_edge = [&](int u, int v){
		gph[u].erase(gph[u].find(v));
		gph[v].erase(gph[v].find(u));
	};
	vector<pair<int, int>> pcand(n, pi(-1, -1));
	vector<int> ord(n, -1);
	int piv = 0;
	while(sz(que)){
		int x = que.front();
		que.pop();
		if(ord[x] != -1) continue;
		ret.bags[x].push_back(x);
		ord[x] = piv++;
		if(sz(gph[x]) == 1){
			int y = *gph[x].begin();
			rem_edge(x, y);
			ret.bags[x].push_back(y);
			if(sz(gph[y]) <= 2) que.push(y);
			pcand[x] = pi(y, y);
		}
		if(sz(gph[x]) == 2){
			int u = *gph[x].begin();
			int v = *gph[x].rbegin();
			rem_edge(x, u);
			rem_edge(x, v);
			gph[u].insert(v);
			gph[v].insert(u);
			ret.bags[x].push_back(u);
			ret.bags[x].push_back(v);
			if(sz(gph[u]) <= 2) que.push(u);
			if(sz(gph[v]) <= 2) que.push(v);
			pcand[x] = pi(u, v);
		}
	}
	if(piv != n) return ret;
	ret.valid = true;
	int root = -1;
	for(int i = 0; i < n; i++){
		if(pcand[i].first == -1){
			if(root != -1) ret.par[i] = root;
			else root = i;
			continue;
		}
		if(ord[pcand[i].first] < ord[pcand[i].second]) swap(pcand[i].first, pcand[i].second);
		ret.par[i] = pcand[i].second;
	}
	return ret;
}
 
using edge_t = long long;
struct edge{
	int s, e;
	edge_t x, y;
};
 
namespace TWSPSolver{
	const int MAXK = 3; // (treewidth) + 1
	const int MAXL = 19; 
	const int MAXN = 300005;
	const edge_t INF = 4e18;
 
	pi vertexToBags[MAXN];
	bool check[MAXN][MAXK];
	vector<int> gph[MAXN];
	int comp[MAXL][MAXN];
	edge_t dist[MAXL][MAXK][MAXN];
	edge_t rdist[MAXL][MAXK][MAXN];
	edge_t inter[MAXN][MAXK][MAXK]; 
	edge_t aux[MAXN][MAXK][MAXK][2];
	int dep[MAXN], par[MAXN], vis[MAXN];
 
	struct node{
		int u, v;
		edge_t dist;
		bool operator<(const node &nd)const{
			return dist > nd.dist;
		}
	};
	vector<vector<int>> bags;
 
	vector<int> dfn;
	int sz[MAXN], msz[MAXN];
 
	void dfs(int x, int p){
		dfn.push_back(x);
		sz[x] = 1;
		msz[x] = 0;
		for(auto &y : gph[x]){
			if(y != p && !vis[y]){
				dfs(y, x);
				sz[x] += sz[y];
				msz[x] = max(msz[x], sz[y]);
			}
		}
	}
 
	int get_center(int x){
		dfn.clear();
		dfs(x, -1);
		pi ret(1e9, 1e9);
		for(auto &v : dfn){
			int w = max(sz(dfn) - sz[v], msz[v]);
			ret = min(ret, pi(w, v));
		}
		return ret.second;
	}
	
	int parc[MAXN];
	void tfill(int x, int p, int v){
		dfn.push_back(x);
		parc[x] = p;
		for(auto &y : gph[x]){
			if(!vis[y] && y != p){
				comp[v][y] = comp[v][x];
				tfill(y, x, v);
			}
		}
	}
	void init(int n, vector<edge> _edges, vector<int> tpar, vector<vector<int>> _bags){
		bags = _bags;
		fill(vertexToBags, vertexToBags + n, pi(-1, -1));
		for(int i = 0; i < sz(bags); i++){
			sort(all(bags[i]));
			memset(check[i], 0, sizeof(check[i]));
			for(int j = 0; j < sz(bags[i]); j++){
				if(vertexToBags[bags[i][j]] == pi(-1, -1)){
					vertexToBags[bags[i][j]] = pi(i, j);
					check[i][j] = 1;
				}
			}
		}
		vector<tuple<int, int, edge_t>> edges;
		for(auto &x : _edges){
			edges.emplace_back(x.s, x.e, x.x);
			edges.emplace_back(x.e, x.s, x.y);
		}
		sort(all(edges));
		for(int i = 0; i < sz(bags); i++){
			for(int j = 0; j < sz(bags[i]); j++){
				for(int k = 0; k < sz(bags[i]); k++){
					if(j == k) continue;
					else{
						auto l = lower_bound(all(edges), make_tuple(bags[i][j], bags[i][k], -1));
						if(l != edges.end() && get<0>(*l) == bags[i][j] && get<1>(*l) == bags[i][k]){
							inter[i][j][k] = get<2>(*l);
						}
						else inter[i][j][k] = INF;
					}
				}
			}
		}
		memset(dep, 0, sizeof(int) * sz(bags));
		memset(par, -1, sizeof(int) * sz(bags));
		memset(vis, 0, sizeof(int) * sz(bags));
		for(int i = 0; i < sz(bags); i++) gph[i].clear();
		for(int i = 0; i < MAXL; i++){
			for(int j = 0; j < MAXK; j++){
				fill(dist[i][j], dist[i][j] + n, INF);
				fill(rdist[i][j], rdist[i][j] + n, INF);
			}
		}
		for(int i = 0; i < sz(tpar); i++){
			if(tpar[i] != -1){
				gph[tpar[i]].push_back(i);
				gph[i].push_back(tpar[i]);
			}
		}
		priority_queue<node> pq;
		queue<int> que;
		que.push(0);
		while(sz(que)){
			int x = que.front();
			que.pop();
			int nx = get_center(x);
			if(par[x] != -1){
				par[nx] = par[x];
				dep[nx] = dep[x];
			}
			x = nx;
			comp[dep[x]][x] = x;
			dfn.clear();
			tfill(x, -1, dep[x]);
			reverse(all(dfn));
			for(auto &v : dfn){
				int S = sz(bags[v]);
				for(auto &w : gph[v]){
					if(!vis[w] && parc[w] == v){
						for(int a = 0; a < sz(bags[w]); a++){
							for(int b = 0; b < a; b++){
								for(int t1 = 0; t1 < S; t1++){
									if(bags[w][a] != bags[v][t1]) continue;
									for(int t2 = 0; t2 < t1; t2++){
										if(bags[w][b] != bags[v][t2]) continue;
										inter[v][t1][t2] = min(inter[v][t1][t2], inter[w][a][b]);
										inter[v][t2][t1] = min(inter[v][t2][t1], inter[w][b][a]);
									}
								}
							}
						}
					}
				}
				for(int i = 0; i < S; i++){
					for(int j = 0; j < S; j++){
						for(int k = 0; k < S; k++){
							inter[v][j][k] = min(inter[v][j][k], inter[v][j][i] + inter[v][i][k]);
						}
					}
				}
			}
			reverse(all(dfn));
			for(auto &v : dfn){
				for(int i = 0; i < MAXK; i++){
					for(int j = 0; j < MAXK; j++){
						aux[v][i][j][0] = aux[v][i][j][1] = INF;
					}
				}
			}
			int S = sz(bags[x]);
			for(int i = 0; i < S; i++) aux[x][i][i][0] = aux[x][i][i][1] = 0;
			for(auto &v : dfn){
				for(int j = 0; j < S; j++){
					for(int k = 0; k < sz(bags[v]); k++){
						for(int l = 0; l < sz(bags[v]); l++){
							aux[v][j][l][0] = min(aux[v][j][l][0], aux[v][j][k][0] + inter[v][k][l]);
							aux[v][j][l][1] = min(aux[v][j][l][1], aux[v][j][k][1] + inter[v][l][k]);
						}
					}
				}
				for(auto &w : gph[v]){
					if(!vis[w] && parc[w] == v){
						for(int a = 0; a < sz(bags[v]); a++){
							int b = find(all(bags[w]), bags[v][a]) - bags[w].begin();
							if(b < sz(bags[w])){
								for(int c = 0; c < S; c++){
									aux[w][c][b][0] = min(aux[w][c][b][0], aux[v][c][a][0]);
									aux[w][c][b][1] = min(aux[w][c][b][1], aux[v][c][a][1]);
								}
							}
						}
					}
				}
			}
			for(auto &p : dfn){
				for(int q = 0; q < sz(bags[p]); q++){
					if(check[p][q]){
						int v = bags[p][q];
						for(int c = 0; c < S; c++){
							dist[dep[x]][c][v] = min(dist[dep[x]][c][v], aux[p][c][q][0]);
							rdist[dep[x]][c][v] = min(rdist[dep[x]][c][v], aux[p][c][q][1]);
						}
					}
				}
 
			}
			vis[x] = 1;
			for(auto &y : gph[x]){
				if(!vis[y]){
					que.push(y);
					par[y] = x;
					dep[y] = dep[x] + 1;
					for(int a = 0; a < sz(bags[y]); a++){
						for(int b = 0; b < a; b++){
							for(int t1 = 0; t1 < S; t1++){
								if(bags[y][a] != bags[x][t1]) continue;
								for(int t2 = 0; t2 < t1; t2++){
									if(bags[y][b] != bags[x][t2]) continue;
									inter[y][a][b] = min(inter[y][a][b], inter[x][t1][t2]);
									inter[y][b][a] = min(inter[y][b][a], inter[x][t2][t1]);
								}
							}
						}
					}
				}
			}
		}
	}
 
	edge_t query(int u, int v){
		pi tu = vertexToBags[u];
		pi tv = vertexToBags[v];
		int lv = min(dep[tu.first], dep[tv.first]);
		while(comp[lv][tu.first] != comp[lv][tv.first]) lv--;
		int c = comp[lv][tu.first];
		edge_t ret = INF;
		for(int i = 0; i < sz(bags[c]); i++){
			ret = min(ret, rdist[lv][i][u] + dist[lv][i][v]);
		}
		return ret;
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, k, q; cin >> n >> k >> q;
	vector<int> a(n), l(n, 1), r(n, 1);
	for(int i = 0; i < n; i++) cin >> a[i];
	vector<edge> edges;
	{
		vector<int> stk;
		for(int i = 0; i < n; i++){
			while(sz(stk) && a[stk.back()] < a[i]){
				edges.push_back({stk.back(), i, r[stk.back()], l[i]}); 
				stk.pop_back();
			}
			if(sz(stk)){
				edges.push_back({stk.back(), i, r[stk.back()], l[i]}); 
			}
			while(sz(stk) && a[stk.back()] == a[i]) stk.pop_back();
			stk.push_back(i);
		}
		stk.clear();
		for(int i = n - 1; i >= 0; i--){
			while(sz(stk) && a[stk.back()] < a[i]){
				edges.push_back({stk.back(), i, l[stk.back()], r[i]}); 
				stk.pop_back();
			}
			if(sz(stk)){
				edges.push_back({stk.back(), i, l[stk.back()], r[i]}); 
			}
			while(sz(stk) && a[stk.back()] == a[i]) stk.pop_back();
			stk.push_back(i);
		}
	}
	vector<pi> edg;
	for(auto &e : edges){
		edg.emplace_back(e.s, e.e);
	}
	auto dcmp = tree_decomposition(n, edg);
	assert(dcmp.valid);
	TWSPSolver::init(n, edges, dcmp.par, dcmp.bags);
	for(int i = 0; i < q; i++){
		int s, t; cin >> s >> t;
		cout << TWSPSolver::query(s - 1, t - 1) - 1 << "\n";
	}
}


