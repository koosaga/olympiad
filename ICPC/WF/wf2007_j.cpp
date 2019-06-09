#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;

const int MAXN = 55;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct mf{
	struct edg{ int pos, cap, rev; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, x, (int)gph[s].size()-1});
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

int cut[MAXN];

int main(){
	int n, m;
	cin >> n >> m;
	vector<pi> v(m);
	for(auto &i : v) cin >> i.first >> i.second;
	for(int i=1; i<=n; i++){
		for(auto &j : v){
			mf.add_edge(j.first, j.second, 1);
		}
		cut[i] = mf.match(0, i);
		mf.clear();
	}
	cut[0] = 1e9;
	bool upd = true;
	while(upd){
		upd = false;
		vector<int> punk(cut + 1, cut + n + 1);
		sort(punk.begin(), punk.end());
		punk.resize(unique(punk.begin(), punk.end()) - punk.begin());
		for(auto &i : punk){
			for(int j=1; j<=n; j++){
				if(cut[j] <= i) continue;
				for(auto &j : v){
					if(cut[j.first] > i && cut[j.second] > i){
						mf.add_edge(j.first, j.second, 1);
					}
				}
				int dap = mf.match(0, j) + i;
				if(cut[j] > dap){
					upd = true;
					cut[j] = dap;
				}
				mf.clear();
			}
		}
	}
	cout << cut[1] << endl;
}
