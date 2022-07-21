#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
 
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 2005;
 
struct edg{
	int pos; lint cap; int rev;
};
vector<edg> gph[MAXN];
void clear(){
	for(int i = 0; i < MAXN; i++) gph[i].clear();
}
 
void add_edge(int s, int e, lint x){
	gph[s].push_back({e, x, sz(gph[e])});
	gph[e].push_back({s, 0, sz(gph[s]) - 1});
}
int dis[MAXN], pnt[MAXN];
 
bool bfs(int src, int sink) {
	memset(dis, 0, sizeof(dis));
	memset(pnt, 0, sizeof(pnt));
	queue<int> que; que.push(src); dis[src] = 1;
	while(sz(que)){
		int x = que.front(); que.pop();
		for(auto &e : gph[x]){
			if(e.cap > 0 && !dis[e.pos]){
				dis[e.pos] = dis[x] + 1;
				que.push(e.pos);
			}
		}
	}
	return dis[sink] > 0;
}
 
lint dfs(int x, int sink, lint f){
	if(x == sink) return f;
	for(; pnt[x] < sz(gph[x]); pnt[x]++){
		edg e = gph[x][pnt[x]];
		if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
			lint w = dfs(e.pos, sink, min(f, e.cap));
			if(w){
				gph[x][pnt[x]].cap -= w;
				gph[e.pos][e.rev].cap += w;
				return w;
			}
		}
	}
	return 0;
}
 
lint flow(int src, int sink){
	lint ret = 0;
	while(bfs(src, sink)){
		lint r;
		while((r = dfs(src, sink, 1e18))) ret += r;
	}
	return ret;
}
 
int vis[MAXN];
 
void dfs2(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &y : gph[x]){
		if(y.cap > 0) dfs2(y.pos);
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
		int n, m; cin >> n >> m;
		int s, t; cin >> s >> t; s--; t--;
		add_edge(2 * n, 2 * s, 1e18);
		add_edge(2 * n, 2 * t + 1, 1e18);
		add_edge(2 * s + 1, 2 * n + 1, 1e18);
		add_edge(2 * t, 2 * n + 1, 1e18);
		for(int i = 0; i < m; i++) {
			int s, e, x;
			cin >> s >> e >> x;
			s--;
			e--;
			add_edge(2 * s, 2 * e + 1, x);
			add_edge(2 * s + 1, 2 * e, x);
			add_edge(2 * e, 2 * s + 1, x);
			add_edge(2 * e + 1, 2 * s, x);
		}
		cout << flow(2 * n, 2 * n + 1) << "\n";
		dfs2(2 * n);
		for(int i = 0; i < n; i++){
			if(vis[2*i] && !vis[2*i+1]) cout << "A";
			else if(vis[2*i+1] && !vis[2*i]) cout << "B";
			else cout << "C";
		}
		cout <<"\n";
}
