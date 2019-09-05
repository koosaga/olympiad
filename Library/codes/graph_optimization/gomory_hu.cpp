struct edg{ int s, e, x; };
vector<edg> edgs;
maxflow mf;
void clear(){ edgs.clear(); }
void add_edge(int s, int e, int x){ edgs.push_back({s, e, x}); }
bool vis[MAXN];
void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : mf.gph[x]) if(i.cap > 0) dfs(i.pos);
}
vector<pi> solve(int n){ // i - j cut : i - j minimum edge cost. 0 based.
	vector<pi> ret(n); // if i > 0, stores pair(parent,cost)
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