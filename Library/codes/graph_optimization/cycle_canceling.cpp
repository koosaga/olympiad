// Cycle canceling (Dual of successive shortest path)
// Time complexity is ridiculously high (F * maxC * nm^2). But runs reasonably in practice (V = 70 in 1s)
struct edg{ int pos, cap, rev, cost; };
vector<edg> gph[MAXN];
void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
void add_edge(int s, int e, int x, int c){
	gph[s].push_back({e, x, (int)gph[e].size(), c});
	gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
}
int dist[MAXN], par[MAXN], pae[MAXN];
int negative_cycle(int n){
	bool mark[MAXN] = {};
	memset(dist, 0, sizeof(dist));
	int upd = -1;
	for(int i=0; i<=n; i++){
		for(int j=0; j<n; j++){
			int idx = 0;
			for(auto &k : gph[j]){
				if(k.cap > 0 && dist[k.pos] > dist[j] + k.cost){
					dist[k.pos] = dist[j] + k.cost;
					par[k.pos] = j;
					pae[k.pos] = idx;
					if(i == n){
						upd = j;
						while(!mark[upd]){
							mark[upd] = 1;
							upd = par[upd];
						}
						return upd;
					}
				}
				idx++;
			}
		}
	}
	return -1;
}
int match(int n){
	int rt = -1;
	int ans = 0;
	while(~(rt = negative_cycle(n))){
		bool mark[MAXN] = {};
		vector<pi> cyc;
		while(!mark[rt]){
			cyc.push_back(pi(par[rt], pae[rt]));
			mark[rt] = 1;
			rt = par[rt];
		}
		reverse(cyc.begin(), cyc.end());
		int capv = 1e9;
		for(auto &i : cyc){
			auto e = &gph[i.first][i.second];
			capv = min(capv, e->cap);
		}
		for(auto &i : cyc){
			auto e = &gph[i.first][i.second];
			e->cap -= capv;
			gph[e->pos][e->rev].cap += capv;
			ans += e->cost * capv;
		}
	}
	return ans;
}
