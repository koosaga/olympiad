#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

	const int MAXN = 105;
namespace MCMF{
	struct edg{ int pos, cap, rev; double cost; };
	vector<edg> gph[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
	void add_edge(int s, int e, int x, double c){
		gph[s].push_back({e, x, (int)gph[e].size(), c});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
	}
	double dist[MAXN];
	int pa[MAXN], pe[MAXN];
	bool inque[MAXN];
	bool spfa(int src, int sink){
		fill(dist, dist + MAXN, 1e9);
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
				if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost + 0.001){
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
	double match(int src, int sink){
		double ret = 0;
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

}

int n;
complex<double> a[MAXN];

void solve(){
	MCMF::clear();
	cin >> n;
	if(n == 0) exit(0);
	for(int i=0; i<n; i++){
		int x, y; cin >> x >> y;
		a[i] = complex<double>(x, y);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i != j) MCMF::add_edge(i + 1, j + n + 1, 1, abs(a[i] - a[j]));
			else MCMF::add_edge(i + 1, j + n + 1, 1, 1e9);
		}
		MCMF::add_edge(0, i + 1, 1, 0);
		MCMF::add_edge(i + n + 1, 2 * n + 1, 1, 0);
	}
	printf("%.2f\n", MCMF::match(0, 2*n+1) / 2);
}

int main(){
	while(1){
		solve();
	}
}

