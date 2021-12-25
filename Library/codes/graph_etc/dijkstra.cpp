#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;

vector<pi> gph[MAXN];

vector<lint> dijkstra(int s, int n){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	vector<lint> dist(n, 1e18);
	auto enq = [&](int x, lint v){
		if(dist[x] > v){
			dist[x] = v;
			pq.emplace(v, x);
		}
	};
	enq(s, 0);
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &[w, y] : gph[x.second]) enq(y, w + x.first);
	}
	return dist;
}

void add_edge(int s, int e, int x){
	gph[s].emplace_back(x, e);
}
