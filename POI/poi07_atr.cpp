#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 20005;

vector<pi> gph[MAXN];
priority_queue<pi, vector<pi>, greater<pi> > pq;
int n, m, k;
int dist[25][MAXN];
int dp[1<<20][20];
int adj[25][25];

int main(){
	scanf("%d %d %d",&n,&m,&k);
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	int q; scanf("%d",&q);
	while(q--){
		int x, y;
		scanf("%d %d",&x,&y);
		x -= 2;
		y -= 2;
		adj[x][y] = 1;
	}
	for(int i=1; i<=k+1; i++){
		dist[i][i] = 0;
		pq.push(pi(0, i));
		while(!pq.empty()){
			auto x = pq.top();
			pq.pop();
			if(dist[i][x.second] != x.first) continue;
			for(auto &j : gph[x.second]){
				if(dist[i][j.second] > x.first + j.first){
					dist[i][j.second] = x.first + j.first;
					pq.push(pi(dist[i][j.second], j.second));
				}
			}
		}
	}
	if(k == 0){
		cout << dist[1][n] << endl;
		return 0;
	}
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0; i<k; i++) dp[(1<<i)][i] = dist[1][i+2];
	for(int i=1; i<(1<<k); i++){
		for(int j=0; j<k; j++){
			if((i >> j) % 2 == 0) continue;
			bool ok = 1;
			for(int l=0; l<k; l++){
				if((i >> l) % 2 && adj[j][l]) ok = 0;
			}
			if(!ok) continue;
			for(int l=0; l<k; l++){
				dp[i][j] = min(dp[i][j], dp[i ^ (1<<j)][l] + dist[l+2][j+2]);
			}
		}
	}
	int ret = 1e9;
	for(int i=0; i<k; i++) ret = min(ret, dist[i+2][n] + dp[(1<<k)-1][i]);
	cout << ret << endl;
}

