#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

const int MAXN = 405;
struct maxflow{
	struct edg{int pos, cap, rev;};
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
	}

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
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
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
}maxflow;

int n, f, d;

int main(){
	cin >> n >> f >> d;
	for(int i=1; i<=f; i++){
		maxflow.add_edge(0, i, 1);
	}
	for(int i=1; i<=d; i++){
		maxflow.add_edge(n+f+n+i, n+f+n+d+1, 1);
	}
	for(int i=1; i<=n; i++){
		int x, y, p;
		scanf("%d %d",&x,&y);
		for(int j=0; j<x; j++){
			scanf("%d",&p);
			maxflow.add_edge(p, f+i, 1);
		}
		maxflow.add_edge(f+i, f+i+n, 1);
		for(int j=0; j<y; j++){
			scanf("%d",&p);
			maxflow.add_edge(f+i+n, n+f+p+n, 1);
		}
	}
	cout << maxflow.match(0, n+f+d+1+n);
}
