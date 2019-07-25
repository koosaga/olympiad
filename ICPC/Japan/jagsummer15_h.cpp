#include <bits/stdc++.h>
using namespace std;
using pi = complex<double>;
const double eps = 1e-8;
const int MAXN = 666;

struct mcmf{
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
				if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost + eps){
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
}mcmf;

int n;
pi s[MAXN], e[MAXN];

pi read(){
	int x, y; cin >> x >> y;
	return pi(x, y);
}

int main(){
	scanf("%d %*d %*d",&n);
	double ret = 0;
	for(int i=1; i<=n; i++){
		s[i] = read();
		e[i] = read();
		ret += abs(s[i] - e[i]);
	}
	for(int i=1; i<=n; i++){
		mcmf.add_edge(0, i, 1, 0);
		mcmf.add_edge(i + n, 2 * n + 1, 1, 0);
		for(int j=1; j<=n; j++){
			mcmf.add_edge(i, j + n, 1, abs(s[i] - e[j]));
		}
	}
	printf("%.10f",ret + mcmf.match(0, 2*n+1));
}
