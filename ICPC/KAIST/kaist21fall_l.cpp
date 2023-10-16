#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 4005;

struct edg{
	int s, e; lint x;
};

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
	bool spfa(int src, int sink){
		memset(dist, 0x3f, sizeof(dist));
		memset(inque, 0, sizeof(inque));
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
		memset(new_dist, 0x3f, sizeof(new_dist));
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

	lint findPath(int s, int e, int n){
		lint ans = dijkstra(s, e, n).second + dist[e] - dist[s];
		if(ans > 0) return 0;
		return -ans;
	}

	void match(int src, int sink, int n){
		spfa(src, sink);
		pair<bool, lint> qq;
		while((qq = dijkstra(src, sink, n)).first){
			for(int i = 0; i < n; i++) dist[i] += min(lint(2e15), new_dist[i]);
			int cap = 1e9;
			for(int pos = sink; pos != src; pos = pa[pos]){
				cap = min(cap, gph[pa[pos]][pe[pos]].cap);
			}
			for(int pos = sink; pos != src; pos = pa[pos]){
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= cap;
				gph[pos][rev].cap += cap;
			}
		}
	}
	int getMatched(int x){
		for(auto &y : gph[x]){
			if(y.pos == 0) continue;
			if(y.cap == 0) return y.pos;
		}
		return -1;
	}
}mf;

int main(){
	int n, m, k;
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1; i <= n; i++) mf.add_edge(0, i, 1, 0);
	for(int i = n+1; i <= n+m; i++) mf.add_edge(i, n+m+1, 1, 0);
	mf.add_edge(n+m+1, n+m+2, m+1, 0);
	mf.add_edge(0, n+m+1, m+1, 0);
	vector<edg> v;
	for(int i = 0; i < k; i++){
		int s, e;
		lint x;
		scanf("%d %d %lld",&s,&e,&x);
		s--; e--;
		v.push_back({s, e, x});
		mf.add_edge(s + 1, e + n + 1, 1, -x);
	}
	mf.match(0, n + m + 2, n + m + 3);
	vector<int> matched(n);
	for(int i = 0; i < n; i++){
		matched[i] = mf.getMatched(i + 1) - (n + 1);
	}
	for(auto &i : v){
		if(matched[i.s] != i.e) puts("0");
		else{
			lint ff = i.x - mf.findPath(i.s + 1, i.e + n + 1, n + m + 3);
			printf("%lld\n", ff);
		}
	}
}


