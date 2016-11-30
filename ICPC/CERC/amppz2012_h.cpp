#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> gph[200005];
int n, c1[200005], c2[200005];
int dp[200005], vis[200005], instk[200005];

int dfs(int x){
	if(instk[x]) return 1e9;
	if(vis[x]) return dp[x];
	vis[x] = 1;
	instk[x] = 1;
	dp[x] = c1[x];
	for(int j=0; j<gph[x].size(); j++){ int i = gph[x][j];
		dp[x] += dfs(i);
		dp[x] = min(dp[x], 1087654321);
	}
	instk[x] = 0;
	dp[x] = min(dp[x], c2[x]);
	return dp[x];
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		scanf("%d %d",&c1[i],&c2[i]);
		int k;
		scanf("%d",&k);
		gph[i].resize(k);
		for(int j=0; j<k; j++) scanf("%d",&gph[i][j]);
	}
	cout << dfs(1);
}