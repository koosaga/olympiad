#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1000;

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
 
	int match(int src, int sink){
		int ret = 0;
		while(bfs(src, sink)){
			int minv = 1e9;
			for(int pos = sink; pos != src; pos = pa[pos]){
				minv = min(minv, gph[pa[pos]][pe[pos]].cap);
			}
			for(int pos = sink; pos != src; pos = pa[pos]){
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= minv;
				gph[pos][rev].cap += minv;
			}
			ret += minv;
		}
		return ret;
	}
}maxflow;
 
int main(){
	int n;
	cin >> n;
	for(int i=1; i<n; i++){
		int k;
		scanf("%d",&k);
		while(k--){
			int x;
			scanf("%d",&x);
			if(i == 1 || x == n) maxflow.add_edge(i, x, 1);
			else maxflow.add_edge(i, x, 1e9);
		}
	}
	cout << maxflow.match(1, n);
}
