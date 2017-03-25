#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

const int MAXN = 405;
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
		int cnt = 0;
		while(spfa(src, sink)){
			cnt++;
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
		if(cnt < sink/2){
			puts("NIE");
			exit(0);
		}
		return ret;
	}
}mcmf;

int n;

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		int x, s, e, k;
		cin >> x >> s >> e >> k;
		for(int j=s; j<=e; j++){
			mcmf.add_edge(i, j+n, 1, k * abs(x - j));
		}
		mcmf.add_edge(0, i, 1, 0);
		mcmf.add_edge(i+n, n+n+1, 1, 0);
	}
	cout << mcmf.match(0, 2*n+1);
}

