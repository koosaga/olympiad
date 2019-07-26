#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 505;

struct nf{
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

int n, w;
pi a[MAXN];

lint dist(pi a, pi b){
	lint dx = b.first - a.first;
	lint dy = b.second - a.second;
	return dx * dx + dy * dy;
}

int main(){
	scanf("%*d %d %d",&w,&n);
	for(int i=1; i<=n; i++){
		cin >> a[i].first >> a[i].second;
		if(a[i].second >= w - 100) mf.add_edge(0, 2*i-1, 1e9);
		if(a[i].second <= 100) mf.add_edge(2*i, 2*n+1, 1e9);
		mf.add_edge(2*i-1, 2*i, 1);
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(dist(a[i], a[j]) <= 40000){
				mf.add_edge(2*j, 2*i-1, 1e9);
			}
		}
	}
	cout << mf.match(0, 2*n+1) << endl;
}
