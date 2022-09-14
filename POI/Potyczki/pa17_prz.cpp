#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 3005;
const int MAXE = 500005;


struct strongly_connected{
	vector<vector<int>> gph;

	void init(int n){
		gph.clear();
		gph.resize(n);
	}

	void add_edge(int s, int e){
		gph[s].push_back(e);
	}

	vector<int> val, comp, z, cont;
	int Time, ncomps;
	template<class G, class F> int dfs(int j, G& g, F f) {
		int low = val[j] = ++Time, x; z.push_back(j);
		for(auto e : g[j]) if (comp[e] < 0)
			low = min(low, val[e] ?: dfs(e,g,f));

		if (low == val[j]) {
			do {
				x = z.back(); z.pop_back();
				comp[x] = ncomps;
				cont.push_back(x);
			} while (x != j);
			f(cont); cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	template<class G, class F> void scc(G& g, F f) {
		int n = sz(g);
		val.assign(n, 0); comp.assign(n, -1);
		Time = ncomps = 0;
		for(int i=0; i<n; i++) if (comp[i] < 0) dfs(i, g, f);
	}

	int piv;
	void get_scc(int n){
		scc(gph, [&](vector<int> &v){});
		for(int i=0; i<n; i++){
			comp[i] = ncomps - comp[i];
		}
		piv = ncomps;
	}
}scc;


struct disj{
	int pa[MAXN], sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
	void add(int x, int v){
		sz[find(x)] += v;
	}
}disj;

int cnt[MAXN][MAXN];
int par[MAXN], dep[MAXN], din[MAXN], dout[MAXN], piv;
vector<pi> gph[MAXN];
bool isTreeEdge[MAXE];

bool in(int u, int v){ return din[u] <= din[v] && dout[v] <= dout[u]; }

void dfs(int x, int p = -1){
	din[x] = ++piv;
	for(auto &[idx, y] : gph[x]){
		if(idx == p) continue;
		if(!dep[y]){
			par[y] = x;
			dep[y] = dep[x] + 1;
			isTreeEdge[idx] = 1;
			dfs(y, idx);
		}
		else if(dep[y] < dep[x]){
			cnt[dep[y]][din[x]]++;
		}
	}
	dout[x] = piv;
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, q; cin >> n >> m >> q;
	vector<pi> edges;
	for(int i = 0; i < m; i++){
		int u, v; cin >> u >> v;
		u--; v--;
		gph[u].emplace_back(i, v);
		gph[v].emplace_back(i, u);
		edges.emplace_back(u, v);
	}
	dep[0] = 1;
	dfs(0);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cnt[i][j] += cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
		}
	}
	int S = 0;
	while(q--){
		int r; cin >> r;
		vector<pi> newEdges;
		vector<pi> points;
		vector<int> comp = {0};
		for(int j = 0; j < r; j++){
			int x, puv, pvu;
			cin >> x >> puv >> pvu;
			x = (x + S) % m;
			int u = edges[x].first, v = edges[x].second;
			if(!puv) newEdges.emplace_back(u, v);
			if(!pvu) newEdges.emplace_back(v, u);
			if(isTreeEdge[x]){
				if(dep[u] < dep[v]) comp.push_back(v);
				else comp.push_back(u);
			}
			else{
				if(dep[u] < dep[v]) points.emplace_back(dep[u], din[v]);
				else points.emplace_back(dep[v], din[u]);
			}
		}
		sort(all(comp), [&](int x, int y){ return din[x] < din[y]; });
		comp.resize(unique(all(comp)) - comp.begin());
		vector<int> stk;
		vector<int> pars(sz(comp));
		vector<vector<int>> sons(sz(comp));
		disj.init(sz(comp));
		for(int i = 0; i < sz(comp); i++){
			while(sz(stk) && !in(comp[stk.back()], comp[i])) stk.pop_back();
			int S = dout[comp[i]] - din[comp[i]] + 1;
			disj.add(i, S);
			if(sz(stk)){
				pars[i] = stk.back();
				sons[pars[i]].push_back(i);
				disj.add(stk.back(), -S);
			}
			stk.push_back(i);
		}
		stk.clear();
		auto sum = [&](int sx, int ex, int sy, int ey){
			return cnt[ex][ey] - cnt[sx-1][ey] - cnt[ex][sy-1] + cnt[sx-1][sy-1];
		};
		auto sum_in = [&](int sx, int ex, int sy, int ey){
			int ret = 0;
			for(auto &[x, y] : points){
				if(sx <= x && x <= ex && sy <= y && y <= ey) ret++;
			}
			return ret;
		};
		for(int i = 0; i < sz(comp); i++){
			while(sz(stk) && !in(comp[stk.back()], comp[i])) stk.pop_back();
			stk.push_back(i);
			if(sz(stk) > 1){
				for(int j = sz(stk) - 2; j >= 0; j--){
					int u = comp[stk[j]];
					int v = comp[stk[j+1]];
					int sumTot = sum(dep[u], dep[v] - 1, din[comp[i]], dout[comp[i]]);
					int sumInTot = sum_in(dep[u], dep[v] - 1, din[comp[i]], dout[comp[i]]);
					for(auto &k : sons[i]){
						sumTot -= sum(dep[u], dep[v] - 1, din[comp[k]], dout[comp[k]]);
						sumInTot -= sum_in(dep[u], dep[v] - 1, din[comp[k]], dout[comp[k]]);
					}
					if(sumTot > sumInTot){
						disj.uni(stk[j], i);
					}
				}
			}
		}
		auto locate = [&](int x){
			int s = 0, e = sz(comp) - 1;
			while(s != e){
				int m = (s + e + 1) / 2;
				if(din[comp[m]] <= din[x]) s = m;
				else e = m - 1;
			}
			while(!in(comp[s], x)) s = pars[s];
			return s;
		};
		scc.init(sz(comp));	
		for(auto &[x, y] : newEdges){
			x = locate(x);
			y = locate(y);
			x = disj.find(x);
			y = disj.find(y);
			scc.add_edge(x, y);
		}
		scc.get_scc(sz(comp));
		vector<int> memb(sz(comp) + 2, -1);
		for(int i = 0; i < sz(comp); i++){
			int w = scc.comp[i];
			if(memb[w] != -1) disj.uni(i, memb[w]);
			memb[w] = i;
		}
		set<int> s;
		for(int i = 0; i < sz(comp); i++){
			if(disj.find(i) == i){
				s.insert(i);
			}
		}
		for(auto &[x, y] : newEdges){
			x = disj.find(x);
			y = disj.find(y);
			if(x != y && s.count(x)) s.erase(x);
		}
		if(sz(s) > 1) cout << "0\n";
		else{
			int ans = disj.sz[disj.find(*s.begin())];
			cout << ans << "\n";
			S = (S + ans) % m;
		}
	}
}

