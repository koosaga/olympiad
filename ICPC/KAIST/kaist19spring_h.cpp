#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;
using pi = pair<int, int>;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear();	}
	void add_edge(int l, int r){ gph[l].push_back(r); }
	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<n; i++){
			if(l[i] == -1 && !dis[i]){
				que.push(i);
				dis[i] = 1;
			}
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}
	bool dfs(int x){
		if(vis[x]) return 0;
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				l[x] = i; r[i] = x;
				return 1;
			}
		}
		return 0;
	}
	int match(int n){
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		int ret = 0;
		while(bfs(n)){
			memset(vis, 0, sizeof(vis));
			for(int i=0; i<n; i++) if(l[i] == -1 && dfs(i)) ret++;
		}
		return ret;
	}
}bpm;

int n, m;
vector<pi> gph[MAXN];
vector<int> rev[MAXN];
int par[MAXN], pae[MAXN];
lint dap[MAXN * 2];	
map<pi, int> mp;

void add_flow(int s, int e, int x){
	dap[mp[pi(s, e)]] += x;
}

lint dfs(int x){
	lint compensate = n - 1;
	for(auto &i : gph[x]){
		lint new_flux = dfs(i.second);
		if(new_flux > 0)add_flow(i.first, x, new_flux);
		compensate -= new_flux;
	}
	if(compensate > 0) add_flow(pae[x], x, compensate);
	return n - compensate;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		rev[e].push_back(s);
		if(e < n) bpm.add_edge(s, e);
		mp[pi(s, e)] = i;
	}
	if(bpm.match(n) != n - 1){
		puts("-1");
		return 0;
	}
	queue<int> que;
	que.push(n);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : rev[x]){
			if(!par[bpm.l[i]]){
				par[bpm.l[i]] = x;
				pae[bpm.l[i]] = i;
				que.push(bpm.l[i]);
			}
		}
	}
	for(int i=1; i<n; i++){
		if(!par[i]){
			puts("-1");
			return 0;
		}
		gph[par[i]].emplace_back(pae[i], i);
	}
	dfs(n);
	for(int i=0; i<m; i++) printf("%lld\n", dap[i]);
}
