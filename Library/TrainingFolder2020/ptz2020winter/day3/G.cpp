#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, m;
vector<int> gph[MAXN];

namespace dcmp{
	vector<int> tr[MAXN];
	vector<int> dfn;
	bool vis[MAXN];
	int dep[MAXN], sz[MAXN], msz[MAXN], par[MAXN], len[MAXN];
	int dist[17][11][MAXN];
	int tmin[11][MAXN];
	void add_edge(int s, int e){
		tr[s].push_back(e);
		tr[e].push_back(s);
	}
	void dfs(int x, int p){
		sz[x] = 1;
		msz[x] = 0;
		dfn.push_back(x);
		for(auto &i : tr[x]){
			if(i != p && !vis[i]){
				dfs(i, x);
				sz[x] += sz[i];
				msz[x] = max(msz[x], sz[i]);
			}
		}
	}
	int get_center(int x){
		dfn.clear();
		dfs(x, -1);
		pi ans(1e9, 1e9);
		for(auto &i : dfn){
			int val = max(msz[i], (int)dfn.size() - sz[i]);
			ans = min(ans, pi(val, i));
		}
		return ans.second;
	}
	int query(int v){
		int ans = 1e9;
		for(int i=v; i; i = par[i]){
			for(int j=0; j<len[i]; j++){
				ans = min(ans, tmin[j][i] + dist[dep[i]][j][v]);
			}
		}
		return ans;
	}
	void mark(int v){
		for(int i=v; i; i = par[i]){
			for(int j=0; j<len[i]; j++){
				tmin[j][i] = min(tmin[j][i], dist[dep[i]][j][v]);
			}
		}
	}
	int sub[MAXN];
	void dfsf(int x, int p){
		for(auto &i : tr[x]){
			if(!vis[i] && i != p){
				sub[i] = sub[x];
				dfsf(i, x);
			}
		}
	}
	void solve(int x = 1, int p = 0){
		if(!p){
			memset(dist, 0x3f, sizeof(dist));
			memset(tmin, 0x3f, sizeof(tmin));
		}
		x = get_center(x);
		if(p){
			dep[x] = dep[p] + 1;
			par[x] = p;
		}
		sub[x] = x;
		for(auto &i : tr[x]){
			if(!vis[i]){
				sub[i] = i;
				dfsf(i, x);
			}
		}
		queue<int> que;
		que.push(x);
		dist[dep[x]][0][x] = 0;
		vector<int> mid;
		while(sz(que)){
			auto v = que.front(); que.pop();
			for(auto &i : gph[v]){
				if(sub[i] && dist[dep[x]][0][i] > dist[dep[x]][0][v] + 1){
					dist[dep[x]][0][i] = dist[dep[x]][0][v] + 1;
					que.push(i);
				}
			}
			bool chk = 0;
			for(auto &i : gph[v]){
				if(sub[i] && i != x && v != x && sub[v] != sub[i] && v < i) chk = 1;
			}
			if(chk) mid.push_back(v);
		}
		assert(sz(mid) <= 10);
		len[x] = sz(mid) + 1;
		for(int i=0; i<sz(mid); i++){
			dist[dep[x]][i + 1][mid[i]] = 0;
			que.push(mid[i]);
			while(sz(que)){
				int v = que.front(); que.pop();
				for(auto &j : gph[v]){
					if(sub[j] && dist[dep[x]][i + 1][j] > dist[dep[x]][i + 1][v] + 1){
						dist[dep[x]][i + 1][j] = dist[dep[x]][i + 1][v] + 1;
						que.push(j);
					}
				}
			}
		}
		vis[x] = 1;
		sub[x] = 0;
		for(auto &i : tr[x]){
			if(!vis[i]){
				sub[i] = 0;
				dfsf(i, x);
			}
		}
		for(auto &i : tr[x]){
			if(!vis[i]) solve(i, x);
		}
	}
}

struct disj{
	int pa[MAXN];
	void init(int n){ iota(pa, pa + n + 1, 0); }
	int find(int x){ return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int main(){
	scanf("%d %d %*d",&n,&m);
	disj.init(n);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
		if(disj.uni(s, e)) dcmp::add_edge(s, e);
	}
	dcmp::solve();
	int q; scanf("%d",&q);
	while(q--){
		int t, v; scanf("%d %d",&t,&v);
		if(t == 1) dcmp::mark(v);
		else printf("%d\n", dcmp::query(v));
	}
}
