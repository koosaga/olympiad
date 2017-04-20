#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

const int MAXN = 1005;

struct maxflow{
	struct edg{int pos, cap, rev;};
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
	  
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
	}
	  
	int pa[MAXN], pe[MAXN];

	bool bfs(int src, int sink){
		bool vis[MAXN] = {};
		queue<int> que;
		que.push(src);
		vis[src] = 1;
		while(!que.empty()){
			int x = que.front(); 
			que.pop();
			if(x == sink) return 1;
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > 0 && !vis[e.pos]){
					vis[e.pos] = 1;
					pa[e.pos] = x;
					pe[e.pos] = i;
					que.push(e.pos);
				}
			}
		}
		return 0;
	}

	int imp[505];
	void match(int src, int sink, int n, int t, int m, int flow_lim){
		int ret = 0, cnt = 0;
		for(int i=0; i<t && i < flow_lim; i++){
			for(int j=1; j<=n; j++){
				if(imp[j]) continue;
				if(bfs(j, sink)){
					int minv = 1e9;
					for(int pos = sink; pos != j; pos = pa[pos]){
						minv = min(minv, gph[pa[pos]][pe[pos]].cap);
					}
					for(int pos = sink; pos != j; pos = pa[pos]){
						int rev = gph[pa[pos]][pe[pos]].rev;
						gph[pa[pos]][pe[pos]].cap -= minv;
						gph[pos][rev].cap += minv;
					}
					ret++;
					cnt += i + 1;
				}
				else{
					imp[j] = 1;
				}
			}
		}
		printf("%d %d\n", ret, cnt * m);
		for(int j=1; j<=n; j++){
			int tmp = 0;
			for(auto &k : gph[j]){
				if(k.cap == 0){
					printf("%d %d %d\n", j, k.pos - n, tmp);
					tmp += m;
				}
			}
		}
	}
}maxflow;
 
int n, m, r, t, k;

int main(){
	cin >> n >> m >> r >> t >> k;
	for(int i=0; i<k; i++){
		int l, r;
		scanf("%d %d",&l,&r);
		maxflow.add_edge(l, r+n, 1);
	}
	for(int i=1; i<=m; i++){
		maxflow.add_edge(i+n, n+m+1, 1);
	}
	maxflow.match(-1, n+m+1, n, t/r, r, m);
}