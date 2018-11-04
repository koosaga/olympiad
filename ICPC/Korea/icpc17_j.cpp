#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 205;

struct maxflow{
	struct edg{ int pos, cap, rev; };
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
					dis[e.pos] = dis[x] + 1;
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
				if(w){
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
}mf;

pi e[5050];
int n, m;

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		cin >> e[i].first >> e[i].second;
		e[i].first--;
		e[i].second--;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			mf.clear();
			for(int k=0; k<n; k++) mf.add_edge(2*k, 2*k+1, 1);
			for(int k=0; k<m; k++){
				mf.add_edge(e[k].first * 2 + 1, 2 * e[k].second, 1e9);
				mf.add_edge(e[k].second * 2 + 1, 2 * e[k].first, 1e9);
			}
			int w = mf.match(2 * i + 1, 2 * j);
			if(w < n / 2){
				puts("-1");
				return 0;
			}
		}
	}
	puts("1");
}
