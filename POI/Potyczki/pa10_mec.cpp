#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 6000;

struct mf{
	struct edg{int pos, cap, rev; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
	}
	int dis[MAXN], pnt[MAXN];
	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &e : gph[x]){
				if(e.cap > 0 && !dis[e.pos]){
					dis[e.pos] = dis[x] +1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}
	int dfs(int x, int sink, int f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
				int w = dfs(e.pos, sink, min(f, e.cap));
				if(w > 0){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
	lint match(int src, int sink){
		lint ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
}maxflow;

int n, m, s[MAXN], e[MAXN], win[MAXN];
int cur[MAXN];
int adj[105][105];

bool solve(int x){
	memcpy(cur, win, sizeof(cur));
	vector<pi> edg;
	int current_goal = win[x];
	for(int i=1; i<=n; i++){
		if(x != i && !adj[x][i]){
			cur[x] += 2;
		}
	}
	maxflow.clear();
	for(int i=1; i<=n; i++){
		for(int j=1; j<i; j++){
			if(i == x || j == x) continue;
			if(!adj[i][j]){
				edg.emplace_back(i, j);
			}
		}
	}
	for(int i=0; i<edg.size(); i++){
		maxflow.add_edge(i + n + 1, x, 2);
	}
	for(int i=1; i<=n; i++){
		if(i == x) continue;
		if(cur[x] < cur[i]) return 0;
		maxflow.add_edge(0, i, cur[x] - cur[i]);
		for(int j=0; j<edg.size(); j++){
			if(i == edg[j].first || i == edg[j].second){
				maxflow.add_edge(i, j + n + 1, 2);
			}
		}
	}
	return maxflow.match(0, x) == 2 * edg.size();
}

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int p, q;
		scanf("%d %d %d %d",&s[i],&e[i],&p,&q);
		if(p < q) win[e[i]] += 2;
		if(p > q) win[s[i]] += 2;
		if(p == q) win[s[i]] += 1, win[e[i]] += 1;
		adj[s[i]][e[i]] = 1;
		adj[e[i]][s[i]] = 1;
	}
	for(int i=1; i<=n; i++){
		if(solve(i)) printf("%d ", i);
	}
}