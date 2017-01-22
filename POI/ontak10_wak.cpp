#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

const int MAXN = 605;
struct mincostflow{
	struct edg{ int pos, cap, rev, cost; };
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}

	void add_edge(int s, int e, int x, int c){
		gph[s].push_back((edg){e, x, (int)gph[e].size(), c});
		gph[e].push_back((edg){s, 0, (int)gph[s].size()-1, -c});
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

int n, k, a[666];

int main(){
	cin >> n >> k;
	for(int i=0; i<3*n; i++){
		int x;
		cin >> x;
		mcmf.add_edge(i, min(i + n, 3*n), 1, -x);
		mcmf.add_edge(i, i+1, k, 0);
	}
	mcmf.add_edge(3*n, 3*n+1, k, 0);
	cout << -mcmf.match(0, 3*n+1);
}
