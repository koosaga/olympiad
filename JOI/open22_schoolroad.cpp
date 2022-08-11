#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct dtree{
vector<int> E[MAXN], RE[MAXN], rdom[MAXN];

int S[MAXN], RS[MAXN], cs;
int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN];

void clear(int n) {
	cs = 0;
	for(int i=0;i<=n;i++) {
		par[i] = val[i] = sdom[i] = rp[i] = dom[i] = S[i] = RS[i] = 0;
		E[i].clear(); RE[i].clear(); rdom[i].clear();
	}
}
void addEdge(int x, int y) { E[x].push_back(y); }
void Union(int x, int y) { par[x] = y; }
int Find(int x, int c = 0) {
	if(par[x] == x) return c ? -1 : x;
	int p = Find(par[x], 1);
	if(p == -1) return c ? par[x] : val[x];
	if(sdom[val[x]] > sdom[val[par[x]]]) val[x] = val[par[x]];
	par[x] = p;
	return c ? p : val[x];
}
void dfs(int x) {
	RS[ S[x] = ++cs ] = x;
	par[cs] = sdom[cs] = val[cs] = cs;
	for(int e : E[x]) {
		if(S[e] == 0) dfs(e), rp[S[e]] = S[x];
		RE[S[e]].push_back(S[x]);
	}
}
int solve(int s, int *up) { // Calculate idoms
	dfs(s);
	for(int i=cs;i;i--) {
		for(int e : RE[i]) sdom[i] = min(sdom[i], sdom[Find(e)]);
		if(i > 1) rdom[sdom[i]].push_back(i);
		for(int e : rdom[i]) {
			int p = Find(e);
			if(sdom[p] == i) dom[e] = i;
			else dom[e] = p;
		}
		if(i > 1) Union(i, rp[i]);
	}
	for(int i=2;i<=cs;i++) if(sdom[i] != dom[i]) dom[i] = dom[dom[i]];
	for(int i=2;i<=cs;i++) up[RS[i]] = RS[dom[i]];
	return cs;
}
}dtree1, dtree2;

vector<pi> gph[MAXN];
vector<int> g[2][MAXN];
lint d1[MAXN], d2[MAXN];
int par1[MAXN], par2[MAXN];
int din[2][MAXN], dout[2][MAXN], piv;

bool inSub(int i, int u, int v){
	return din[i][u] <= din[i][v] && dout[i][v] <= dout[i][u];
}

void dfs(int i, int x, int p = -1){
	din[i][x] = piv++;
	for(auto &j : g[i][x]){
		if(j == p) continue;
		dfs(i, j, x);
	}
	dout[i][x] = piv;
}

void dijkstra(int s, lint *d){
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	d[s] = 0;
	pq.emplace(d[s], s);
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(d[x.second] != x.first) continue;
		for(auto &y : gph[x.second]){
			if(d[y.second] > y.first + x.first){
				d[y.second] = y.first + x.first;
				pq.emplace(d[y.second], y.second);
			}
		}
	}
}

struct edge{
	int s, e, x;
};

bool findPath(int s, int e, vector<edge> edges){
	//cout << "instance " << s << " " << e <<  endl;
	vector<int> vlist;
	for(auto &x : edges){
	//	cout << x.s << " " << x.e << " " << x.x << endl;
		vlist.push_back(x.s);
		vlist.push_back(x.e);
	}
	sort(all(vlist));
	vlist.resize(unique(all(vlist)) - vlist.begin());
	for(auto &v : vlist){
		d1[v] = d2[v] = 1e18;
		gph[v].clear();
	}
	for(auto &x : edges){
		gph[x.s].emplace_back(x.x, x.e);
		gph[x.e].emplace_back(x.x, x.s);
	}
	dijkstra(s, d1);
	dijkstra(e, d2);
	dtree1.clear(sz(vlist) + 1);
	dtree2.clear(sz(vlist) + 1);
	for(auto &i : vlist){
		if(d1[i] + d2[i] != d1[e]){
			return 1;
		}
		for(auto &[w, j] : gph[i]){
			if(abs(d1[i] - d1[j]) != w){
				return 1;
			}
			if(d1[i] < d1[j]) dtree1.addEdge(i, j);
			if(d1[i] > d1[j]) dtree2.addEdge(i, j);
		}
	}
	dtree1.solve(s, par1);
	dtree2.solve(e, par2);
	for(auto &i : vlist){
		if(i != s) g[0][par1[i]].push_back(i);
		if(i != e) g[1][par2[i]].push_back(i);
	}
	dfs(0, s); piv = 0;
	dfs(1, e); piv = 0;
	for(auto &i : vlist){
		g[0][i].clear();
		g[1][i].clear();
	}
	for(auto &i : vlist){
		for(auto &[w, j] : gph[i]){
			if(d1[i] < d1[j] && !inSub(0, i, j) && !inSub(1, j, i)){
				return 1;
			}
		}
	}
	return 0;
}

namespace BCC{
	vector<pi> gph[MAXN];
	vector<int> bcc[MAXN], cmp[MAXN];
	int c;
	int dfn[MAXN], low[MAXN], par[MAXN], pae[MAXN], dep[MAXN], piv;
	void addEdge(int s, int e, int i){
		gph[s].emplace_back(i, e);
		gph[e].emplace_back(i, s);
	}
	void dfs(int x, int p){
		dfn[x] = low[x] = ++piv;
		for(auto &[i, y] : gph[x]){
			if(i == p) continue;
			if(!dfn[y]){
				par[y] = x;
				pae[y] = i;
				dep[y] = dep[x] + 1;
				dfs(y, i);
				low[x] = min(low[x], low[y]);
			}
			else low[x] = min(low[x], dfn[y]);
		}
	}
	void color(int x, int p){
		if(p){
			bcc[p].push_back(x);
			cmp[x].push_back(p);
		}
		for(auto &[e, i] : gph[x]){
			if(cmp[i].size()) continue;
			if(low[i] >= dfn[x]){
				bcc[++c].push_back(x);
				cmp[x].push_back(c);
				color(i, c);
			}
			else color(i, p);
		}
	}
	pair<vector<vector<int>>, vector<pi>> getPaths(int s, int e, int n){
		dfs(s, -1);
		color(s, 0);
		vector<vector<int>> edgeBcc(c);
		vector<int> bccEdge(MAXN, -1);
		for(int i = 0; i < n; i++){
			set<int> s;
			for(auto &x : cmp[i]) s.insert(x);
			for(auto &[idx, j] : gph[i]){
				if(dep[j] <= dep[i]) continue;
				edgeBcc[cmp[j][0] - 1].push_back(idx);
				bccEdge[idx] = cmp[j][0] - 1;
			//	cout << cmp[j][0] - 1 << " " << i << " " << j << endl;
			}
		}
		vector<int> epath;
		vector<int> vtx;
		for(int i = e; i != s; i = par[i]){
			epath.push_back(pae[i]);
			vtx.push_back(i);
		}
		vtx.push_back(s);
		vector<vector<int>> edges;
		vector<pi> vertices;
		for(int i = 0; i < sz(epath); ){
			int j = i;
			while(j < sz(epath) && bccEdge[epath[i]] == bccEdge[epath[j]]) j++;
			edges.push_back(edgeBcc[bccEdge[epath[i]]]);
			vertices.emplace_back(vtx[i], vtx[j]);
			i = j;
		}
		return make_pair(edges, vertices);
	}
}

int main(){
	// in case of general: check this for all bccs in path?
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, m; cin >> n >> m;
	vector<edge> edges;
	for(int i = 0; i < m; i++){
		int s, e, x; cin >> s >> e >> x;
		s--; e--;
		edges.push_back({s, e, x});
		BCC::addEdge(s, e, i);
	}
	auto gp = BCC::getPaths(0, n - 1, n);
	for(int i = 0; i < sz(gp.first); i++){
		vector<edge> sol;
		vector<int> v = gp.first[i];
		for(int j = 0; j < sz(v); j++) sol.push_back(edges[v[j]]);
		if(findPath(gp.second[i].first, gp.second[i].second, sol)){
			cout << "1\n";
			return 0;
		}
	}
	cout << "0\n";
	return 0;
}
