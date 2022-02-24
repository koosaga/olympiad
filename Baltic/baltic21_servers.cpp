#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int MAXN = 120005;

vector<pi> gph[MAXN];

namespace CD{
	int sz[MAXN], msz[MAXN], vis[MAXN];
	vector<int> dfn;
	void dfs(int x, int p = -1){
		sz[x] = 1;
		msz[x] = 0;
		dfn.push_back(x);
		for(auto &[_, y] : gph[x]){
			if(y != p && !vis[y]){
				dfs(y, x);
				sz[x] += sz[y];
				msz[x] = max(msz[x], sz[y]);
			}
		}
	}
	int get_center(int x){
		dfn.clear();
		dfs(x);
		pi ret(1e9, -1);
		for(auto &v : dfn){
			int val = max(msz[v], sz(dfn) - sz[v]);
			ret = min(ret, pi(val, v));
		}
		return ret.second;
	}
	pi good[17][MAXN];
	pi can[17][MAXN];
	void dfs2(int x, int l, int r, int p, vector<pi> &strg, int depth){
		can[depth][x] = pi(l, r);
		strg.emplace_back(l, r);
		for(auto &[c, y] : gph[x]){
			if(!vis[y] && y != p && r < c) dfs2(y, l, c, x, strg, depth);
		}
	}
	void dfs3(int x, int l, int r, int p, int depth){
		good[depth][x].second = 1;
		good[depth][x].first = l;
		for(auto &[c, y] : gph[x]){
			if(!vis[y] && y != p && r > c) dfs3(y, l, c, x, depth);
		}
	}
	int par[MAXN], dep[MAXN];
	vector<pi> ds[MAXN];
	void init(int n){
		memset(can, 0x3f, sizeof(can));
		queue<pi> que;
		que.push(pi(1, -1));
		while(sz(que)){
			int x = que.front().first;
			int p = que.front().second;
			que.pop();
			x = get_center(x);
			vis[x] = 1;
			par[x] = p;
			if(~p) dep[x] = dep[p] + 1;
			good[dep[x]][x] = pi(-1e9, 1);
			can[dep[x]][x] = pi(1e9, -1e9);
			for(auto &[c, y] : gph[x]){
				if(vis[y]) continue;
				que.emplace(y, x);
				dfs2(y, c, c, -1, ds[x], dep[x]);
				dfs3(y, c, c, -1, dep[x]);
			}
		}
	}
	int ans[MAXN];
	struct query{
		int x, y, idx;
	};
	vector<query> qry[MAXN];
	void query(int v, int hi, int stackIdx){
		for(int w = v; ~w; w = par[w]){
			if(!good[dep[w]][v].second) continue;
			if(good[dep[w]][v].first > hi) continue;
			int lo = good[dep[w]][v].first + 1;
			ans[stackIdx]++;
			qry[w].push_back({lo, hi, stackIdx});
		}
	}
	int lca(int x, int y){
		if(dep[x] > dep[y]) swap(x, y);
		while(dep[x] < dep[y]) y = par[y];
		while(x != y){
			x = par[x], y = par[y];
		}
		return x;
	}
	bool reach(int u, int v, int d){
		int l = lca(u, v);
		if(!good[dep[l]][u].second) return 0;
		if(can[dep[l]][v].second > d) return 0;
		if(good[dep[l]][u].first > d) return 0;
		if(good[dep[l]][u].first > can[dep[l]][v].first) return 0;
		return 1;
	}
	struct bit{
		int tree[MAXN];
		void add(int x, int v){
			if(x <= 0) return;
			for(int i = x; i < MAXN; i += i & -i) tree[i] += v;
		}
		int query(int x){
			if(x <= 0) return 0;
			int ret = 0;
			for(int i = x; i; i -= i & -i) ret += tree[i];
			return ret;
		}
	}bit;
	vector<int> sweep(int n, int q){
		for(int i = 1; i <= n; i++){
			sort(all(qry[i]), [&](struct query a, struct query b){
				return a.y < b.y;
			});
			for(auto &[x, y] : ds[i]) swap(x, y);
			sort(all(ds[i]));
			int j = 0;
			for(auto &p : qry[i]){
				while(j < sz(ds[i]) && ds[i][j].first <= p.y){
					bit.add(ds[i][j++].second, 1);
				}
				ans[p.idx] += bit.query(MAXN - 1) - bit.query(p.x - 1);
			}
			while(j > 0){
				bit.add(ds[i][--j].second, -1);
			}
		}
		return vector<int>(ans, ans + q);
	}
};

struct query{
	int t, u, v, lim, idx;
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	int c = 0;
	vector<query> qry;
	for(int i = 0; i < n+q-1; i++){
		string s; cin >> s;
		if(s == "S"){
			int u, v; cin >> u >> v;
			c++;
			gph[u].emplace_back(c, v);
			gph[v].emplace_back(c, u);
		}
		else if(s == "Q"){
			int u, v; cin >> u >> v;
			int sq = sz(qry);
			qry.push_back({1, v, u, c, sq});
		}
		else{
			int sq = sz(qry);
			int u; cin >> u;
			qry.push_back({2, u, -1, c, sq});
		}
	}
	CD::init(n);
	for(auto &i : qry){
		if(i.t == 2) CD::query(i.u, i.lim, i.idx);
	}
	auto swp = CD::sweep(n, sz(qry));
	for(auto &i : qry){
		if(i.t == 1) cout << (CD::reach(i.u, i.v, i.lim) ? "yes" : "no") << "\n";
		else cout << swp[i.idx] << "\n";
	}
}
