#include <bits/stdc++.h>
#define sz(v) ((lint)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

struct strongly_connected{
	vector<vector<int>> gph;

	void init(){
		gph.clear();
	}

	void add_edge(int s, int e){
		s--, e--;
		if(sz(gph) <= s) gph.resize(s + 1);
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
	int get_scc_and_solve(int n, int m){
		gph.resize(n);
		scc(gph, [&](vector<int> &v){});
		for(int i=0; i<n; i++){
			comp[i] = ncomps - comp[i];
		}
		piv = ncomps;
		vector<int> vtx(n);
		iota(all(vtx), 0);
		sort(all(vtx), [&](const int &a, const int &b){
			return comp[a] > comp[b];
		});
		vector<int> cnt(piv + 1);
		for(int i=0; i<m; i++){
			cnt[comp[i]]++;
		}
		int w = 0;
		int ret = 1e9;
		for(int i=piv; i>0; i--){
			bool fuck = 0;
			while(w < sz(vtx) && comp[vtx[w]] == i){
				for(auto &k : gph[vtx[w]]){
					if(comp[k] != i && cnt[comp[k]]) fuck = 1;
				}
				w++;
			}
			if(fuck) cnt[i] = 1e9;
			ret = min(ret, cnt[i]);
		}
		return ret;
	}
}scc;

int par[18][MAXN], dep[MAXN];
int din[MAXN], dout[MAXN], piv;
int color[MAXN];
vector<int> gph[MAXN];
vector<int> grp[MAXN];
int n, k;

void dfs(int x, int p){
	din[x] = piv++;
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
}

int fake[18][MAXN], piv2;

int paint(int x, int p){
	if(~fake[p][x]) return fake[p][x];
	fake[p][x] = ++piv2;
	if(p > 0){
		scc.add_edge(fake[p][x], paint(x, p - 1));
		scc.add_edge(fake[p][x], paint(par[p-1][x], p - 1));
	}
	else{
		scc.add_edge(fake[p][x], color[x]);
	}
	return fake[p][x];
}

int main(){
	memset(fake, -1, sizeof(fake));
	scanf("%d %d",&n,&k);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	auto anc = [&](int x, int p){
		for(int i=0; p; i++){
			if(p & 1) x = par[i][x];
			p >>= 1;
		}
		return x;
	};
	auto lca = [&](int x, int y){
		if(dep[x] > dep[y]) swap(x, y);
		y = anc(y, dep[y] - dep[x]);
		for(int i=17; i>=0; i--){
			if(par[i][x] != par[i][y]){
				x = par[i][x];
				y = par[i][y];
			}
		}
		if(x != y) return par[0][x];
		return x;
	};
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		color[i] = x;
		grp[x].push_back(i);
	}
	piv2 = k;
	scc.init();
	for(int i=1; i<=k; i++){
		sort(all(grp[i]), [&](const int &a, const int &b){
			return din[a] < din[b];
		});
		for(int j=1; j<sz(grp[i]); j++){
			int x = grp[i][j-1], y = grp[i][j];
			int l = lca(x, y);
			if(x != l){
				int dif = dep[x] - dep[l];
				int l = 0;
				while((2 << l) <= dif) l++;
				int v1 = paint(x, l);
				int v2 = paint(anc(x, dif - (1<<l)), l);
				scc.add_edge(i, v1);
				scc.add_edge(i, v2);
			}
			if(y != l){
				int dif = dep[y] - dep[l];
				int l = 0;
				while((2 << l) <= dif) l++;
				int v1 = paint(y, l);
				int v2 = paint(anc(y, dif - (1<<l)), l);
				scc.add_edge(i, v1);
				scc.add_edge(i, v2);
			}
			if(i != color[l]) scc.add_edge(i, color[l]);
		}
	}
	cout << scc.get_scc_and_solve(piv2, k) - 1<< endl;
}
