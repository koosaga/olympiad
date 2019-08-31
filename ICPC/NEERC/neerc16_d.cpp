#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int MAXN = 1005;

struct mcmf{
	struct edg{ int pos, cap, rev, cost, idx; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x, int c, int idx = -1){
		gph[s].push_back({e, x, (int)gph[e].size(), c, idx});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -c, -1});
	}
	lint phi[MAXN], inque[MAXN], dist[MAXN];
	void prep(int src, int sink){
		memset(phi, 0x3f, sizeof(phi));
		memset(dist, 0x3f, sizeof(dist));
		queue<int> que;
		que.push(src);
		inque[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			inque[x] = 0;
			for(auto &i : gph[x]){
				if(i.cap > 0 && phi[i.pos] > phi[x] + i.cost){
					phi[i.pos] = phi[x] + i.cost;
					if(!inque[i.pos]){
						inque[i.pos] = 1;
						que.push(i.pos);
					}
				}
			}
		}
		for(int i=0; i<MAXN; i++){
			for(auto &j : gph[i]){
				if(j.cap > 0) j.cost += phi[i] - phi[j.pos];
			}
		}
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		pq.push(pi(0, src));
		dist[src] = 0;
		while(!pq.empty()){
			auto l = pq.top();
			pq.pop();
			if(dist[l.second] != l.first) continue;
			for(auto &i : gph[l.second]){
				if(i.cap > 0 && dist[i.pos] > l.first + i.cost){
					dist[i.pos] = l.first + i.cost;
					pq.push(pi(dist[i.pos], i.pos));
				}
			}
		}
	}
	bool vis[MAXN];
	int ptr[MAXN];
	int dfs(int pos, int sink, int flow){
		vis[pos] = 1;
		if(pos == sink) return flow;
		for(; ptr[pos] < gph[pos].size(); ptr[pos]++){
			auto &i = gph[pos][ptr[pos]];
			if(!vis[i.pos] && dist[i.pos] == i.cost + dist[pos] && i.cap > 0){
				int ret = dfs(i.pos, sink, min(i.cap, flow));
				if(ret != 0){
					i.cap -= ret;
					gph[i.pos][i.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	lint match(int src, int sink, int sz = MAXN){
		prep(src, sink);
		for(int i=0; i<sz; i++) dist[i] += phi[sink] - phi[src];
		lint ret = 0;
		int flow = 0;
		while(true){
			memset(ptr, 0, sizeof(ptr));
			memset(vis, 0, sizeof(vis));
			lint tmp = 0;
			while((tmp = dfs(src, sink, 1e9))){
				ret += dist[sink] * tmp;
				flow += tmp;
				memset(vis, 0, sizeof(vis));
			}
			tmp = 1e18;
			for(int i=0; i<sz; i++){
				if(!vis[i]) continue;
				for(auto &j : gph[i]){
					if(j.cap > 0 && !vis[j.pos]){
						tmp = min(tmp, (dist[i] + j.cost) - dist[j.pos]);
					}
				}
			}
			if(tmp > 1e18 - 200) break;
			for(int i=0; i<sz; i++){
				if(!vis[i]) dist[i] += tmp;
			}
		}
		return ret;
	}
}mf;

int n, k, s, e;
int a[MAXN], b[MAXN];

int main(){
	scanf("%d %d %d %d",&n,&k,&e,&s);
	e = k - e;
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++) scanf("%d",&b[i]);
	lint ret = 0;
	for(int i=1; i<=n; i++){
		ret += a[i];
		int s = max(i - k + 1, 1), e = min(i, n - k + 1);
		mf.add_edge(s, e + 1, 1, -(b[i] - a[i]), i);
	}
	mf.add_edge(0, 1, e, 0);
	for(int i=1; i<=n-k+1; i++){
		mf.add_edge(i, i + 1, e - s, 0);
	}
	cout << ret - mf.match(0, n - k + 2) << endl;
	string s;
	for(int i=0; i<n; i++) s.push_back('S');
	for(int i=0; i<MAXN; i++){
		for(auto &j : mf.gph[i]){
			if(j.cap == 0 && j.idx > 0) s[j.idx - 1] = 'E';
		}
	}
	cout << s << endl;
}
