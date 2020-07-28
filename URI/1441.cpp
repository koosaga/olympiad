// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1441
#include <cstdio>
#include <cstring>
int dp[100000],n;
int max(int a,int b){
	if(a > b) return a;
	return b;
}
int solve(int k){
	if(dp[k] != -1) return dp[k];
	if(k % 2 == 0){
		return dp[k] = max(k,solve(k/2));
	}
	else{
		return dp[k] = max(k,solve(3*k+1));
	}
}
int main(){
	memset(dp,-1,sizeof(dp));
	dp[1] = 1;
	while(scanf("%d",&n) && n){
		printf("%d\n",solve(n));
	}
	return 0;
}
