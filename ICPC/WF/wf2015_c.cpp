#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
 
const int MAXN = 210;
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

	bool spfa(int d){
		bool ok = 0;
		memset(dist, 0x3f, sizeof(dist));
		queue<int> que;
		dist[0] = 0;
		inque[0] = 1;
		que.push(0);
		while(!que.empty()){
			int x = que.front();
			que.pop();
			if(x == d) ok = 1;
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

	int match(int sink, int k, int n){
		int ret = 0, dap = 1e9;
		for(int i=0; i<n; i++){
			if(i >= n-k) dap = min(dap, ret);
			spfa(sink);
			int cap = 1e9;
			for(int pos = sink; pos; pos = pa[pos]){
				cap = min(cap, gph[pa[pos]][pe[pos]].cap);
			}
			ret += dist[sink] * cap;
			for(int pos = sink; pos; pos = pa[pos]){
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= cap;
				gph[pos][rev].cap += cap;
			}
		}
		return dap;
	}

	int getcap(int x, int y){
		for(int i=0; i<gph[x].size(); i++){
			if(gph[x][i].pos == y) return gph[x][i].cap;
		}
		return 0;
	}
}mcmf;

int n, k, a[105][105];
int main(){
	cin >> n >> k;
	int ret = 0;
	for(int i=0; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			cin >> a[i][j];
			if(i == 0) ret += a[i][j];
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			mcmf.add_edge(i, j+n, 1, a[i][j] - a[0][j]);
		}
		mcmf.add_edge(0, i, 1, 0);
		mcmf.add_edge(i+n, 2*n+1, 1, 0);
	}
	cout << mcmf.match(2*n+1, k, n) + ret;
}
