// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc12s5
#include <cstdio>
#include <cstring>
int dp[26][26];
int r,c,gatos;
int solve(int x,int y){
	if(x > r || y > c) return 0;
	if(dp[x][y] != -1) return dp[x][y];
	return dp[x][y] = solve(x+1,y) + solve(x,y+1);
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d %d",&r,&c);
	dp[r][c] = 1;
	scanf("%d",&gatos);
	while(gatos--){
		int a,b;
		scanf("%d %d",&a,&b);
		dp[a][b] = 0;
	}
	printf("%d\n",solve(1,1));
	return 0;
}