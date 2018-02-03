#include <bits/stdc++.h>
using namespace std;

int n, m, k, v, t;
int a[17], b[17];
int adj[305][305];
int dp[16][1<<16];

int f(int pos, int msk){
	if(msk == 0) return adj[a[pos]][v];
	if(~dp[pos][msk]) return dp[pos][msk];
	int ret = 1e9;
	for(int i=0; i<k; i++){
		if((msk >> i) & 1){
			ret = min(ret, adj[a[pos]][a[i]] + f(i, msk ^ (1<<i)));
		}
	}
	return dp[pos][msk] = ret;
}

int main(){
	while(true){
		cin >> n >> m >> k >> v >> t;
		if(n == 0) break;
		memset(adj, 0x3f, sizeof(adj));
		memset(dp, -1, sizeof(dp));
		for(int i=1; i<=n; i++) adj[i][i] = 0;
		for(int i=0; i<m; i++){
			int s, e, x;
			cin >> s >> e >> x;
			adj[e][s] = adj[s][e] = min(adj[s][e], x);
		}
		for(int i=0; i<k; i++) cin >> a[i] >> b[i];
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				for(int k=1; k<=n; k++){
					adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
				}
			}
		}
		int ans = 0;
		for(int i=1; i<(1<<k); i++){
			int ret = 1e9, sum = 0, pcnt = 0;
			for(int j=0; j<k; j++){
				if((i >> j) & 1){
					pcnt++;
					ret = min(ret, adj[v][a[j]] + f(j, i ^ (1<<j)));
					sum += b[j];
				}
			}
			if(ret + sum <= t) ans = max(ans, pcnt);
		}
		cout << ans <<endl;
	}
}
