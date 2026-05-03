#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int MAXN = 1005;

struct maxflow{
	struct edg{ int pos, cap, rev; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size() - 1});
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
	bool toSink[MAXN], fromSource[MAXN];
	void dfs2(int x){
		if(fromSource[x]) return;
		fromSource[x] = 1;
		for(auto &i : gph[x]){
			if(i.cap > 0) dfs2(i.pos);
		}
	}
	void dfs3(int x){
		if(toSink[x]) return;
		toSink[x] = 1;
		for(auto &i : gph[x]){
			if(gph[i.pos][i.rev].cap > 0) dfs3(i.pos);
		}
	}
	void precalc(int s, int t){
		memset(toSink, 0, sizeof(toSink));
		memset(fromSource, 0, sizeof(fromSource));
		dfs2(s);
		dfs3(t);
	}
}mf;

int n, m, s, t;

int solve(int x, int y){
	for(auto &i : mf.gph[x]){
		if(i.pos == y && i.cap > 0){
			return mf.toSink[x] && mf.fromSource[y];
		}
	}
	return -69;
}

pi a[MAXN * 12];

int main(){
	while(true){
		scanf("%d %d %d %d",&n,&m,&s,&t);
		if(n+m+s+t == 0) break;
		mf.clear();
		for(int i=0; i<m; i++){
			scanf("%d %d",&a[i].first,&a[i].second);
			mf.add_edge(a[i].first, a[i].second, 1);
		}
		int maxf = mf.match(s, t);
		mf.precalc(s, t);
		int maxv = -1;
		int maxc = 0;
		for(int i=0; i<m; i++){
			int nxt = maxf + solve(a[i].first, a[i].second);
			if(maxv < nxt){
				maxv = nxt;
				maxc = 0;
			}
			if(maxv == nxt) maxc++;
		}
		if(maxv <= maxf) printf("%d %d\n", maxf, 0);
		else printf("%d %d\n", maxv, maxc);
	}
}
