#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
using pi = pair<double, int>;

int n, m;
vector<int> gph[MAXN];
priority_queue<pi, vector<pi>, greater<pi>> pq;
double dist[MAXN], sumDp[MAXN];
bool vis[MAXN];
int deg[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	fill(dist, dist + n + 1, 1e18);
	dist[n] = 0;
	pq.push(pi(dist[n], n));
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(vis[x.second]) continue;
		vis[x.second] = 1;
		for(auto &i : gph[x.second]){
			deg[i]++;
			sumDp[i] += dist[x.second];
			double nxt = 1.0 * gph[i].size() / deg[i];
			nxt += sumDp[i] / deg[i];
			if(dist[i] > nxt){
				dist[i] = nxt;
				pq.push(pi(dist[i], i));
			}
		}
	}
	printf("%.10f\n", dist[1]);
}
