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


int n,m;
int s[205], e[205];
long long adj[205][205];

bool trial(long long t){
	maxflow.clear();
	int sm = 0;
	for (int i=1; i<=n; i++) {
		sm += s[i];
		maxflow.add_edge(0,i,s[i]);
		maxflow.add_edge(i+n,2*n+1,e[i]);
	}
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			if(adj[i][j] <= t){
				maxflow.add_edge(i,j+n,1000);
			}
		}
	}
	return maxflow.match(0, 2*n+1) == sm;
}

int main(){
	memset(adj,0x3f,sizeof(adj));
	scanf("%d %d",&n,&m);
	for (int i=1; i<=n; i++) {
		scanf("%d %d",&s[i],&e[i]);
	}
	for (int i=0; i<m; i++) {
		int s,e,x;
		scanf("%d %d %d",&s,&e,&x);
		adj[e][s] = adj[s][e] = min(adj[s][e],1ll * x);
	}
	for (int i=1; i<=n; i++) {
		adj[i][i] = 0;
	}
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			for (int k=1; k<=n; k++) {
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	long long s = 0, e = 3e11;
	while (s != e) {
		long long m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	if(e > 2e11) puts("-1");
	else printf("%lld",e);
}
