const int MAXN = 505;
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
}mf;

struct circ{
	maxflow mf;
	lint lsum;
	void clear(){
		lsum = 0;
		mf.clear();
	}
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
}circ;

struct gomory_hu{
	struct edg{ int s, e, x; };
	vector<edg> edgs;
	maxflow mf;

	void clear(){
		edgs.clear();
	}

	void add_edge(int s, int e, int x){
		edgs.push_back({s, e, x});
	}

	bool vis[MAXN];

	void dfs(int x){
		if(vis[x]) return;
		vis[x] = 1;
		for(auto &i : mf.gph[x]){
			if(i.cap > 0) dfs(i.pos);
		}
	}

	vector<pi> solve(int n){
		vector<pi> ret(n);
		for(int i=1; i<n; i++){
			for(auto &j : edgs){
				mf.add_edge(j.s, j.e, j.x);
				mf.add_edge(j.e, j.s, j.x);
			}
			ret[i].first = mf.match(i, ret[i].second);
			memset(vis, 0, sizeof(vis));
			dfs(i);
			for(int j=i+1; j<n; j++){
				if(ret[j].second == ret[i].second && vis[j]){
					ret[j].second = i;
				}
			}
			mf.clear();
		}
		return ret;
	}
}gh;