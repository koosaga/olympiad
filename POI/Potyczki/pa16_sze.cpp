#include <bits/stdc++.h>
using namespace std;
const int MAXN = 333;

struct maxflow{
	struct edg{int pos, cap, rev; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size() - 1});
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
				int w = dfs(e.pos, sink, min(e.cap, f));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
	int match(int src, int sink){
		int ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
}mf;

vector<int> crd;
int n, m, s[105], e[105], c[105];

int main(){
	cin >> n >> m;
	int tot = 0;
	for(int i=1; i<=n; i++){
		cin >> s[i] >> e[i] >> c[i];
		crd.push_back(s[i]);
		crd.push_back(e[i]);
		mf.add_edge(0, i, c[i]);
		tot += c[i];
	}
	sort(crd.begin(), crd.end());
	crd.resize(unique(crd.begin(), crd.end()) - crd.begin());
	for(int i=0; i+1<crd.size(); i++){
		mf.add_edge(i + n + 1, 321, (crd[i+1] - crd[i]) * m);
	}
	for(int i=1; i<=n; i++){
		for(int j=0; j+1<crd.size(); j++){
			if(s[i] <= crd[j] && crd[j+1] <= e[i]){
				mf.add_edge(i, j + n + 1, crd[j+1] - crd[j]);
			}
		}
	}
	puts(tot == mf.match(0, 321) ? "TAK" : "NIE");
}