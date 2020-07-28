// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi94p1
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200
using namespace std;
int matriz[MAXN][MAXN],dp[MAXN][MAXN],n;
int solve(int l,int c){
	if(dp[l][c] != -1) return dp[l][c];
	if(l == n){
		return dp[l][c] = matriz[l][c];
	}
	return dp[l][c] = matriz[l][c] + max(solve(l+1,c), solve(l+1,c+1));
}
int main(){
	scanf("%d",&n);
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			scanf("%d",&matriz[i][j]);
		}
	}
	printf("%d\n",solve(1,1));
	return 0;
}