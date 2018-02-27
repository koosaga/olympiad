#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int MAXN = 100005;

vector<pi> gph[MAXN];
int a[4], n, m;
lint dist[4][MAXN];

void dijkstra(lint* d, int x){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, x));
	d[x] = 0;
	while(!pq.empty()){
		auto p = pq.top();
		pq.pop();
		if(d[p.second] != p.first) continue;
		for(auto &i : gph[p.second]){
			if(d[i.second] > p.first + i.first){
				d[i.second] = p.first + i.first;
				pq.push(pi(d[i.second], i.second));
			}
		}
	}
}

lint dp[MAXN];
int ord[MAXN];

lint solve(int v, int w){
	iota(ord, ord + n + 1, 0);
	memset(dp, 0, sizeof(dp));
	sort(ord + 1, ord + n + 1, [&](const int &p, const int &q){
		return dist[v][p] < dist[v][q];
	});
	lint ans = 1e18;
	for(int i=n; i; i--){
		int x = ord[i];
		dp[x] = dist[3][x];
		for(auto &j : gph[x]){
			if(dist[v][x] + j.first + dist[w][j.second] == dist[v][a[w]]){
				dp[x] = min(dp[x], dp[j.second]);
			}
		}
		ans = min(ans, dp[x] + dist[2][x]);
	}
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<4; i++) scanf("%d",&a[i]);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<4; i++) dijkstra(dist[i], a[i]);
	cout << min({solve(0, 1), solve(1, 0), dist[2][a[3]]}) << endl;
}
