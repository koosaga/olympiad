// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1393
#include <cstdio>
#include <cstring>
int dp[50],vis[50],n;
int solve(int k){
	if(k == n) return 1;
	if(k > n) return 0;
	if(vis[k]) return dp[k];
	vis[k] = 1;
	return dp[k] = solve(k+1) + solve(k+2);
}
int main(){
	while(scanf("%d",&n) && n){
		memset(dp,0,sizeof(dp));
		memset(vis,0,sizeof(vis));
		printf("%d\n",solve(0));
	}
	return 0;
}
