#include <bits/stdc++.h>
using namespace std;
const int MAXN = 305;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct gm{
	// 1-based Vertex index
	int vis[MAXN], par[MAXN], orig[MAXN], match[MAXN], aux[MAXN], t, N;
	vector<int> conn[MAXN];
	queue<int> Q;
	void add_edge(int u, int v) {
		u++; v++;
		conn[u].push_back(v); conn[v].push_back(u);
	}
	void init(int n) {
		N = n; t = 0;
		for(int i=0; i<=n; ++i) {
			conn[i].clear();
			match[i] = aux[i] = par[i] = 0;
		}
	}
	void augment(int u, int v) {
		int pv = v, nv;
		do {
			pv = par[v]; nv = match[pv];
			match[v] = pv; match[pv] = v;
			v = nv;
		} while(u != pv);
	}
	int lca(int v, int w) {
		++t;
		while(true) {
			if(v) {
				if(aux[v] == t) return v; aux[v] = t;
				v = orig[par[match[v]]];
			}
			swap(v, w);
		}
	}
	void blossom(int v, int w, int a) {
		while(orig[v] != a) {
			par[v] = w; w = match[v];
			if(vis[w] == 1) Q.push(w), vis[w] = 0;
			orig[v] = orig[w] = a;
			v = par[w];
		}
	}
	bool bfs(int u) {
		fill(vis+1, vis+1+N, -1); iota(orig + 1, orig + N + 1, 1);
		Q = queue<int> (); Q.push(u); vis[u] = 0;
		while(!Q.empty()) {
			int v = Q.front(); Q.pop();
			for(int x: conn[v]) {
				if(vis[x] == -1) {
					par[x] = v; vis[x] = 1;
					if(!match[x]) return augment(u, x), true;
					Q.push(match[x]); vis[match[x]] = 0;
				}
				else if(vis[x] == 0 && orig[v] != orig[x]) {
					int a = lca(orig[v], orig[x]);
					blossom(x, v, a); blossom(v, x, a);
				}
			}
		}
		return false;
	}
	int Match() {
		int ans = 0;
		// find random matching (not necessary, constant improvement)
		vector<int> V(N-1); iota(V.begin(), V.end(), 1);
		shuffle(V.begin(), V.end(), mt19937(0x94949));
		for(auto x: V) if(!match[x]){
			for(auto y: conn[x]) if(!match[y]) {
				match[x] = y, match[y] = x;
				++ans; break;
			}
		}
		for(int i=1; i<=N; ++i) if(!match[i] && bfs(i)) ++ans;
		return ans;
	}
}gm;

int n, m;
vector<int> gph[2][MAXN];
vector<int> dfn, dfn2;
bool vis[MAXN];

vector<pi> paths;
vector<vector<int>> innerVtx;
void dfs1(int x){
	if(vis[x]) return;
	vis[x] = 1;
	dfn.push_back(x);
	for(auto &i : gph[0][x]){
		dfs1(i);
	}
}


vector<int> getInner(int x, int y){
	int idx = 0;
	for(auto &[p, q] : paths){
		if(p == x && q == y){
			auto ans = innerVtx[idx];
			ans.erase(ans.begin());
			ans.erase(--ans.end());
			return ans;
		}
		if(p == y && q == x){
			auto ans = innerVtx[idx];
			ans.erase(ans.begin());
			ans.erase(--ans.end());
			reverse(all(ans));
			return ans;
		}
		idx++;
	}
	vector<int> v;
	return v;
}

void solve(){
//	setbuf(stdout, NULL);
//		puts("ok?");
	for(auto &e : paths){
//		puts("ok?");
		gm.init(2*n);
		for(int i = 0; i < n; i++){
			if(i == e.first || i == e.second) continue;
			gm.add_edge(i, i+n);
		}
		{
			vector<int> vis(n);
			for(auto &f : paths){
				vis[f.first] = vis[f.second] = 1;
				gm.add_edge(f.first, f.second);
			}
			for(int i = 0; i < n; i++){
				for(auto &j : gph[1][i]){
					if(i > j) continue;
					if(!vis[i] && !vis[j]) gm.add_edge(i, j);
					if(!vis[i]) gm.add_edge(i, j + n);
					if(!vis[j]) gm.add_edge(i + n, j);
					gm.add_edge(i + n, j + n);
				}
			}
		}
//		puts("go match");
		if(gm.Match() != n) continue;
//		puts("gotcha");
		for(int i = 0; i < n; i++) gph[0][i].clear();
		for(int i = 0; i < 2 * n; i++){
			int mate = gm.match[i+1] - 1;
			if(mate > i){
				if(mate == i + n) continue;
		//		printf("add edge %d %d\n", i%n, mate%n);
				gph[0][i%n].push_back(mate % n);
				gph[0][mate % n].push_back(i%n);
			}
		}
		memset(vis, 0, sizeof(vis));
		dfn.clear();
		dfs1(e.first);
		assert(sz(dfn) >= 2);
		vector<int> ans;
	//	puts("gotcha");
		for(int i = 0; i < sz(dfn); i++){
			ans.push_back(dfn[i]);
			auto innerVertices = getInner(dfn[i], dfn[(i+1)%sz(dfn)]);
			if(sz(dfn) > 2 || i != 1){
				for(auto &j : innerVertices) ans.push_back(j);
			}
		}
	//	puts("gotcha");
		printf("%d\n", sz(ans));
		for(auto &i : ans) printf("%d\n", i+1);
		exit(0);
	}
	puts("-1");
}

void dfs2(int x, int p = -1){
	dfn2.push_back(x);
	for(auto &i : gph[0][x]){
		if(i != p) dfs2(i, x);
	}
}


void remove_vertex(int v){
	for(auto &x : gph[0][v]){
		gph[0][x].erase(find(all(gph[0][x]), v));
	}
	for(auto &x : gph[1][v]){
		gph[1][x].erase(find(all(gph[1][x]), v));
	}
	gph[0][v].clear(); gph[1][v].clear();
}

int main(){
	int k;
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 0; i < m; i++){
		int s, e; scanf("%d %d",&s,&e);
		s--; e--;
		gph[i >= k][s].push_back(e);
		gph[i >= k][e].push_back(s);
	}
	for(int i = 0; i < n; i++){
		if(!vis[i]){
			dfn.clear();
			dfs1(i);
			if(sz(dfn) == 1) continue;
			bool deg1 = 0;
			bool deg3 = 0;
			for(auto &j : dfn){
				if(sz(gph[0][j]) >= 3){
					deg3 = 1;
				}
				if(sz(gph[0][j]) == 1){
					deg1 = 1;
				}
			}
			if(deg3){
				for(auto &j : dfn){
					remove_vertex(j);
				}
				continue;
			}
			if(!deg1){
				printf("%d\n", sz(dfn));
				for(auto &j : dfn){
					printf("%d\n", j + 1);
				}
				return 0;
			}
			pi ret(-1, -1);
			for(auto &j : dfn){
				if(sz(gph[0][j]) == 1){
					if(ret.first == -1) ret.first = j;
					else ret.second = j;
				}
			}
			dfn2.clear();
			dfs2(ret.first);
			assert(sz(dfn2) >= 2);
			paths.push_back(ret);
			innerVtx.push_back(dfn2);
			for(int i = 1; i < sz(innerVtx.back()) - 1; i++) remove_vertex(innerVtx.back()[i]);
		}
	}
	solve();
}
