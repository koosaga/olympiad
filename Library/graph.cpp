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

const int MAXN = 50005;
const int MAXM = 50005;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXM];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
	}

	void add_edge(int l, int r){
		gph[l].push_back(r);
	}

	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<n; i++){
			if(l[i] == -1 && !dis[i]){
				que.push(i);
				dis[i] = 1;
			}
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}

	bool dfs(int x){
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				vis[r[i]] = 1;
				l[x] = i;
				r[i] = x;
				return 1;
			}
		}
		return 0;
	}

	int match(int n){
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		int ret = 0;
		while(bfs(n)){
			memset(vis, 0, sizeof(vis));
			for(int i=0; i<n; i++){
				if(l[i] == -1 && dfs(i)) ret++;
			}
		}
		return ret;
	} 

	bool chk[MAXN + MAXM];

	void rdfs(int x, int n){
		if(chk[x]) return;
		chk[x] = 1;
		for(int idx=0; idx<gph[x].size(); idx++){
			int i = gph[x][idx];
			chk[i + n] = 1;
			rdfs(r[i], n);
		}
	}

	vector<int> getcover(int n, int m){
		match(n);
		memset(chk, 0, sizeof(chk));
		for(int i=0; i<n; i++){
			if(l[i] == -1) rdfs(i, n);
		}
		vector<int> v;
		for(int i=0; i<n; i++){
			if(!chk[i]) v.push_back(i);
		}
		for(int i=n; i<n+m; i++){
			if(chk[i]) v.push_back(i);
		}
		return v;
	}
}bpm;

const int MAXN = 500;
struct mincostflow{
	struct edg{ int pos, cap, rev, cost; };
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}

	void add_edge(int s, int e, int x, int c){
		gph[s].push_back({e, x, (int)gph[e].size(), c});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
	}

	int dist[MAXN], pa[MAXN], pe[MAXN];
	bool inque[MAXN];

	bool spfa(int src, int sink){
		bool ok = 0;
		memset(dist, 0x3f, sizeof(dist));
		queue<int> que;
		dist[src] = 0;
		inque[src] = 1;
		que.push(src);
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

	int match(int src, int sink){
		int ret = 0;
		while(spfa(src, sink)){
			int cap = 1e9;
			for(int pos = sink; pos != src; pos = pa[pos]){
				cap = min(cap, gph[pa[pos]][pe[pos]].cap);
			}
			ret += dist[sink] * cap;
			for(int pos = sink; pos != src; pos = pa[pos]){
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= cap;
				gph[pos][rev].cap += cap;
			}
		}
		return ret;
	}
}mcmf;

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

namespace stable_marriage{
	vector<vector<int>> rev;
	vector<int> solve(int n, vector<vector<int>> &a, vector<vector<int>> &b){
		rev.clear();
		rev.resize(n);
		vector<int> ret(n), pnt(n), mat(n, -1);
		queue<int> que;
		for(int i=0; i<n; i++){
			rev[i].resize(n);
			for(int j=0; j<n; j++){
				rev[i][b[i][j]] = j;
			}
			que.push(i);
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			int y = a[x][pnt[x]];
			pnt[x]++;
			if(mat[y] == -1){
				mat[y] = x;
				ret[x] = y;
			}
			else{
				if(rev[y][mat[y]] > rev[y][x]){
					que.push(mat[y]);
					mat[y] = x;
					ret[x] = y;
				}
				else que.push(x);
			}
		}
		return ret;
	}
};

const int MAXN = 150000;
struct strongly_connected{
	vector<int> gph[MAXN];
	vector<int> rev[MAXN];
	vector<int> dfn;
	int comp[MAXN], piv;
	bool vis[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
			rev[i].clear();
		}
	}

	void add_edge(int s, int e){
		gph[s].push_back(e);
		rev[e].push_back(s);
	}

	void dfs(int x){
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i]) dfs(i);
		}
		dfn.push_back(x);
	}

	void rdfs(int x, int p){
		comp[x] = p;
		for(auto &i : rev[x]){
			if(!comp[i]) rdfs(i, p);
		}
	}

	void get_scc(int n){
		dfn.clear();
		memset(comp, 0, sizeof(comp));
		memset(vis, 0, sizeof(vis));
		piv = 0;
		for(int i=0; i<n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++piv);
		}
	}
}scc;

struct twosat{
	strongly_connected scc;
	int n;
	bool res[MAXN];

	void init(int _n){
		scc.clear();
		n = _n;
		memset(res, 0, sizeof(res));
	}

	int NOT(int x){
		return x >= n ? (x - n) : (x + n);
	}

	void add_edge(int x, int y){
		if((x >> 31) & 1) x = (~x) + n;
		if((y >> 31) & 1) y = (~y) + n;
		scc.add_edge(x, y);
		scc.add_edge(NOT(y), NOT(x));
	}

	bool satisfy(){
		scc.get_scc(2*n);
		for(int i=0; i<n; i++){
			if(scc.comp[i] == scc.comp[NOT(i)]) return 0;
			if(scc.comp[i] < scc.comp[NOT(i)]) res[i] = 0;
			else res[i] = 1;
		}
		return 1;
	}
}twosat;