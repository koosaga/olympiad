#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 2505;

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
};

namespace circ{
	maxflow mf;
	lint lsum;
	void add_edge(int s, int e, int l, int r){
		lsum += l;
		mf.add_edge(s + 2, e + 2, r - l);
		mf.add_edge(0, e + 2, l);
		mf.add_edge(s + 2, 1, l);
	}
	bool solve(int s, int e){
		mf.add_edge(e+2, s+2, 1e9); 
		return lsum == mf.match(0, 1);
	}
}

int n, m, l, r;
vector<int> cvtx[MAXN];

int main(){
	cin >> n >> m >> l >> r;
	tie(l, r) = pi(m - r, m - l);
	for(int i=1; i<=m; i++){
		int l, r; cin >> l >> r;
		tie(l, r) = pi(n - r, n - l);
		circ::add_edge(2222 + i, 2222 + m + 1, l, r);
	}
	int vtx = n;
	for(int i=1; i<=n; i++){
		circ::add_edge(0, i, l, r);
		int k; cin >> k;
		for(int j=0; j<k; j++){
			int d, l, r;
			cin >> d >> l >> r;
			vtx++;
			cvtx[i].push_back(vtx);
			circ::add_edge(i, vtx, d, r-l+1);
			for(int k=l; k<=r; k++){
				circ::add_edge(vtx, 2222 + k, 0, 1);
			}
		}
	}
	if(!circ::solve(0, 2222 + m + 1)){
		puts("-1");
		return 0;
	}
	puts("1");
	for(int i=1; i<=n; i++){
		vector<int> ans;
		for(auto &j : cvtx[i]){
			for(auto &k : circ::mf.gph[j + 2]){
				if(k.pos > 2222 + 2 && k.cap == 0){
					ans.push_back(k.pos - 2222 - 2);
				}
			}
		}
		sort(ans.begin(), ans.end());
		printf("%d ", (int)ans.size());
		for(auto &j : ans) printf("%d ", j);
		puts("");
	}
}
