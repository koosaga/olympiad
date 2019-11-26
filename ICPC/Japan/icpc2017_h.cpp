#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1205;

struct mf{
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

int easy(vector<pi> c){
	sort(all(c), [&](const pi &a, const pi &b){
		return a.first < b.first;
	});
	int p = 0;
	int ans = 0;
	priority_queue<int, vector<int>, greater<int> > pq;
	for(int i=1; i<=400; i++){
		while(p < sz(c) && c[p].first == i){
			pq.push(c[p++].second);
		}
		while(sz(pq) && pq.top() < i) pq.pop();
		if(sz(pq)){
			ans++;
			pq.pop();
		}
	}
	return ans;
}

int main(){
	int n, m;
	vector<pi> c;
	cin >> n >> m;
	for(int i=0; i<n; i++){
		int x, y; cin >> x >> y; 
		c.emplace_back(x, y);
	}
	printf("%d\n", easy(c));
	for(int i=0; i<n; i++){
		if(i < m){
			mf.add_edge(0, i+1, 1);
			for(int j=c[i].first; j<=c[i].second; j++){
				mf.add_edge(i+1, j+n+2, 1);
			}
		}
		else{
			mf.add_edge(i+1, MAXN-1, 1);
			for(int j=c[i].first; j<=c[i].second; j++){
				mf.add_edge(j+n+2+400, i+1, 1);
			}
		}
	}
	for(int i=1; i<=400; i++){
		mf.add_edge(n+2+i, n+402+i, 1);
	}
	cout << mf.match(0, MAXN - 1) << endl;
}
