#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

lint dist[MAXN][2];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pi>> gph(n+1);
	for(int i = 0; i < m; i++){
		int s, e, x; cin >> s >> e >> x;
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(dist, 0x3f, sizeof(dist));
	auto enq = [&](int x, lint v){
		if(dist[x][v%2] > v){
			dist[x][v%2] = v;
			pq.emplace(v, x);
		}
	};
	enq(1, 0);
	while(sz(pq)){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second][x.first % 2] != x.first) continue;
		for(auto &y : gph[x.second]){
			enq(y.second, y.first + x.first);
		}
	}
	if(dist[n][1] > 1e18) cout << "0\n";
	else cout << dist[n][1] << "\n";
}
