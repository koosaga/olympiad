#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
const int MAXN = 5005;
typedef pair<int, int> pi;

vector<int> gph[MAXN];
int n, dist[MAXN][MAXN], parent[MAXN][MAXN];
int din[MAXN], dout[MAXN], ord[MAXN], piv, dep[MAXN];
int dp[MAXN];

void dfs(int x, int p){
	din[x] = ++piv;
	ord[piv] = x;
	for(auto &i : gph[x]){
		if(i != p){
			parent[1][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x); 
		}
	}
	dout[x] = piv;
}
int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++) parent[0][i] = i;
	dfs(1, 0);
	for(int i=2; i<n; i++){
		for(int j=1; j<=n; j++) parent[i][j] = parent[1][parent[i-1][j]];
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i == j) continue;
			int x = ord[i], y = ord[j];
			if(i < j) dist[x][y] = dist[x][parent[1][y]] + 1;
			else dist[x][y] = dist[parent[1][x]][y] + 1;
		}
	}
	for(int i=n; i>1; i--){
		int x = ord[i];
		int cand[MAXN] = {};
		for(int j=din[x]+1; j<=dout[x]; j++){
			int y = ord[j];
			if(dist[x][y] % 2 == 0) continue;
			int cur = parent[dist[x][y] / 2][y];
			cand[din[parent[1][cur]]] += dp[y];
			cand[dout[parent[1][cur]] + 1] -= dp[y];
			cand[din[cur]] -= dp[y];
			cand[dout[cur] + 1] += dp[y];
		}
		dp[x] = 1e4;
		for(int j=din[x]+1; j<=dout[x]; j++) cand[j] += cand[j-1], dp[x] = min(dp[x], cand[j] + dist[x][ord[j]]);
	//	cout << x << " " << dp[x] << endl;
	}
	int ans = 1e9;
	for(int i=1; i<=n; i++){
		int sum[MAXN] = {};
		for(int j=2; j<=n; j++){
			sum[dist[i][j]] += dp[j];
		}
		for(int j=max(1, dist[1][i]); j<=n; j++) ans = min(ans, sum[j+1] + j);
	}
	cout << ans << endl;
}
