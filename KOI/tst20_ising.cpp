#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 500005;

pi merge(pi a, pi b){
	if(a > b) swap(a, b);
	if(a.first == b.first) b.second += a.second;
	return b;
}

int good_edges, bad_edges;
vector<int> gph[MAXN], ord;
vector<int> backs[MAXN];
int dep[MAXN], add_bad[MAXN], add_good[MAXN];
int din[MAXN], dout[MAXN], piv;
int par[20][MAXN];
pi spt[20][MAXN];

void dfs(int x, int p = -1){
	din[x] = piv++;
	ord.push_back(x);
	for(auto &i : gph[x]){
		if(i != p && !dep[i]){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

bool in_sub(int u, int v){
	return din[u] <= din[v] && dout[v] <= dout[u];
}

lint bino(int n){
	return 1ll * n * (n - 1) / 2;
}

struct kek{
	lint count;
	pi bads;
	kek(){
		count = 0;
		bads = pi(0, 0);
	}
};

pi path_query(int u, int v){
	if(dep[u] <= dep[v]) return pi(-1e9, 0);
	int dx = (dep[u] - dep[v]);
	pi ret(-1e9, 0);
	for(int i=0; dx; i++){
		if(dx & 1){
			ret = merge(ret, spt[i][u]);
			u = par[i][u];
		}
		dx >>= 1;
	}
	return ret;
}

struct foo{
	int u, v, d;
	foo(){}
	foo(int u, int v, int d): u(u), v(v), d(d) {}
	bool operator<(const foo &f)const{
		return d < f.d;
	}
};

priority_queue<foo> pq[MAXN];
foo dp[MAXN];
int idx[MAXN];

lint solve_parent(int n){
	for(auto &x : ord){
		idx[x] = x;
		dp[x] = foo(0, 0, int(1e9));
		for(auto &y : gph[x]){
			if(par[0][y] == x) dp[x] = min(dp[x], dp[y]);
		}
		for(auto &u : backs[x]){
			if(dep[u] % 2 == dep[x] % 2){
				dp[x] = min(dp[x], foo(u, x, dep[u]));
			}
			else{
				pq[x].emplace(u, x, dep[u]);
			}
		}
	}
	lint ret = 0;
	auto func = [&](int x, int is, int ie){
		int good_count = add_good[x];
		int bad_count = bad_edges - add_bad[x];
		auto val = path_query(ie, is);
		if(val.first == bad_count - good_count) return val.second;
		return 0ll;
	};
	for(auto &x : ord){
		if(x == 1) continue;
		// merge heaps
		for(auto &y : gph[x]){
			if(par[0][y] != x) continue;
			if(sz(pq[idx[y]]) > sz(pq[idx[x]])){
				swap(idx[x], idx[y]);
			}
			while(sz(pq[idx[y]])){
				auto tp = pq[idx[y]].top();
				pq[idx[y]].pop();
				pq[idx[x]].push(tp);
			}
		}
		while(sz(pq[idx[x]]) && pq[idx[x]].top().d >= dep[x]) pq[idx[x]].pop();
		int is = 1;
		int ie = par[0][x];
		if(dp[x].d < dep[ie]) ie = dp[x].u;
		if(sz(pq[idx[x]])) is = pq[idx[x]].top().u;
		ret += func(x, is, ie);
	}
	return ret;
}

kek dfs_disjoint(int x){
	kek ret;
	vector<pi> candidates;
	for(auto &i : gph[x]){
		if(par[0][i] == x){
			auto w = dfs_disjoint(i);
			ret.count += w.count;
			if(add_good[i] == 0) w.bads = merge(w.bads, pi(add_bad[i], 1));
			if(w.bads.second) candidates.push_back(w.bads);
		}
	}
	sort(all(candidates));
	pi run(0, 0);
	for(auto &i : candidates){
		if(run.first + i.first == bad_edges){
			ret.count += run.second * i.second;
		}
		run = merge(run, i);
	}
	ret.bads = run;
	return ret;
}

lint count_ways(int N, vector<int> U, vector<int> V){
	vector<pi> edges;
	for(int i=0; i<sz(U); i++){
		edges.emplace_back(U[i], V[i]);
		gph[U[i]].push_back(V[i]);
		gph[V[i]].push_back(U[i]);
	}
	int n = N;
	int m = sz(edges);
	dep[1] = 1;
	dfs(1);
	reverse(all(ord));
	for(auto &[u, v] : edges){
		if(dep[u] > dep[v]) swap(u, v);
		if(dep[u] + 1 < dep[v]){
			backs[v].push_back(u);
			if(dep[u] % 2 == dep[v] % 2){
				bad_edges++;
				add_bad[v]++;
				add_bad[u]--;
			}
			else{
				good_edges++;
				add_good[v]++;
				add_good[u]--;
			}
		}
	}
	for(auto &v : ord){
		if(v == 1) continue;
		add_bad[par[0][v]] += add_bad[v];
		add_good[par[0][v]] += add_good[v];
	}
	// special case: bipartite graph.
	if(bad_edges == 0) return 1;
	// special case: only one edges give contradiction.
	// by above case handling, at least one edge give contradiction.
	{
		int cap = 0;
		if(bad_edges == 1) cap++;
		for(auto &v : ord){
			if(v == 1) continue;
			if(add_good[v] == 0 && add_bad[v] == bad_edges) cap++;
		}
		if(cap > 0) return cap;
	}
	lint ret = 0;
	// 0-respecting cuts
	if(bad_edges == 2) ret += 1;
	// 1-respecting cuts
	for(auto &v : ord){
		if(v == 1) continue;
		if(add_good[v] == 0 && add_bad[v] == bad_edges - 1) ret += 1;
		if(add_good[v] == 1 && add_bad[v] == bad_edges) ret += 1;
	}
	// 2-respecting cuts
	for(int i=2; i<=n; i++){
		spt[0][i] = pi(add_bad[i] - add_good[i], 1);
	}
	for(int i=1; i<20; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
			spt[i][j] = merge(spt[i-1][j], spt[i-1][par[i-1][j]]);
		}
	}
	ret += dfs_disjoint(1).count;
	ret += solve_parent(n);
	return ret;
}


