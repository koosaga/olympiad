#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 2505;

namespace mf{
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
}

int a[55][55];

int main(){
	int tc; cin >> tc;
	for(int i=0; i<tc; i++){
		int n; cin >> n;
		int ans = -100 * n * n;
		mf::clear();
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				double x; cin >> x;
				a[i][j] = (int)round(100 * x);
				int pos = i * n + j + 1;
				mf::add_edge(0, pos, a[i][j]);
				mf::add_edge(pos, n * n + 1, 100 - a[i][j]);
				if(j > 0){
					int e = 100 - abs(a[i][j] - a[i][j-1]);
					mf::add_edge(pos - 1, pos, e);
					mf::add_edge(pos, pos - 1, e);
				}
				if(i > 0){
					int e = 100 - abs(a[i][j] - a[i-1][j]);
					mf::add_edge(pos - n, pos, e);
					mf::add_edge(pos, pos - n, e);
				}
			}
		}
		ans += mf::match(0, n * n + 1);
		ans = -ans;
		printf("%.2f\n", 0.01 * ans);
	}
}
