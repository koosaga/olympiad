#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define move fuck
using namespace std;
const int MAXN = 300005;
const int mod = 1e9 + 7;
using lint = long long;
using llf = long double;
using pi = pair<llf, int>;

int n, m;
vector<int> gph[MAXN];
llf dist[MAXN];
llf prob[MAXN];
llf minDist[MAXN];
bool vis[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	fill(dist, dist + n + 1, 1e18);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	pq.emplace(0, n);
	dist[n] = 0;
	while(!pq.empty()){
		auto x = pq.top(); pq.pop();
		if(vis[x.second]) continue;
		vis[x.second] = 1;
		for(auto &i : gph[x.second]){
			if(dist[i] > 1e17){
				dist[i] = dist[x.second] + 1.5;
				prob[i] = 1;
				minDist[i] = dist[x.second];
				pq.emplace(dist[i], i);
			}
			else if(minDist[i] + 2.0L / 3 >= dist[x.second]){
				prob[i] /= 4;
				llf delta = prob[i] * (1 + 0.75 * dist[x.second] + 0.25 * (minDist[i] + 2) - (minDist[i] + 2));
				if(delta < 0){
					dist[i] += delta;
					pq.emplace(dist[i], i);
				}
			}
		}
	}
	printf("%.10Lf\n", dist[1]);
}
