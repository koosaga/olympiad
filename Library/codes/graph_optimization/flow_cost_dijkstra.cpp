struct mcmf{
	struct edg{ int pos, cap, rev; lint cost; };
	vector<edg> gph[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
	void add_edge(int s, int e, int x, lint c){
		gph[s].push_back({e, x, (int)gph[e].size(), c});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
	}
	lint dist[MAXN];
	int pa[MAXN], pe[MAXN];
	bool inque[MAXN];
	bool spfa(int src, int sink, int n){
		memset(dist, 0x3f, sizeof(dist[0]) * n);
		memset(inque, 0, sizeof(inque[0]) * n);
		queue<int> que;
		dist[src] = 0;
		inque[src] = 1;
		que.push(src);
		bool ok = 0;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			if(x == sink) ok = 1;
			inque[x] = 0;
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost){
					dist[e.pos] = dist[x] + e.cost;
					pa[e.pos] = x;
					pe[e.pos] = i;
					if(!inque[e.pos]){
						inque[e.pos] = 1;
						que.push(e.pos);
					}
				}
			}
		}
		return ok;
	}
	lint new_dist[MAXN];
	pair<bool, lint> dijkstra(int src, int sink, int n){
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		memset(new_dist, 0x3f, sizeof(new_dist[0]) * n);
		new_dist[src] = 0;
		pq.emplace(0, src);
		bool isSink = 0;
		while(sz(pq)){
			auto tp = pq.top(); pq.pop();
			if(new_dist[tp.second] != tp.first) continue;
			int v = tp.second;
			if(v == sink) isSink = 1;
			for(int i = 0; i < gph[v].size(); i++){
				edg e = gph[v][i];
				lint new_weight = e.cost + dist[v] - dist[e.pos];
				if(e.cap > 0 && new_dist[e.pos] > new_dist[v] + new_weight){
					new_dist[e.pos] = new_dist[v] + new_weight;
					pa[e.pos] = v;
					pe[e.pos] = i;
					pq.emplace(new_dist[e.pos], e.pos);
				}
			}
		}
		return make_pair(isSink, new_dist[sink]);
	}

	lint match(int src, int sink, int n){
		spfa(src, sink, n);
		pair<bool, lint> path;
		lint ret = 0;
		while((path = dijkstra(src, sink, n)).first){
			for(int i = 0; i < n; i++) dist[i] += min(lint(2e15), new_dist[i]);
			lint cap = 1e18;
			for(int pos = sink; pos != src; pos = pa[pos]){
				cap = min(cap, (lint)gph[pa[pos]][pe[pos]].cap);
			}
			ret += cap * (dist[sink] - dist[src]);
			for(int pos = sink; pos != src; pos = pa[pos]){
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= cap;
				gph[pos][rev].cap += cap;
			}
		}
		return ret;
	}
}mcmf;
