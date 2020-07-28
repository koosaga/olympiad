// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1522
#include <cstdio>
#include <cstring>
#define MAXN 110
#define MAXL 4
int cartas[MAXN][MAXL], dp[MAXN][MAXN][MAXN],n;
int solve(int topo1, int topo2, int topo3){
	if (topo1 == 0 && topo2 == 0 && topo3 == 0) return 1;
	if (topo1 < 0 || topo2 < 0 || topo3 <0) return 0;
	if (dp[topo1][topo2][topo3] != -1) return dp[topo1][topo2][topo3];
	if (cartas[topo1][1] % 3 == 0 && solve(topo1-1,topo2,topo3)) return dp[topo1][topo2][topo3] = 1;
	if (cartas[topo2][2] % 3 == 0 && solve(topo1,topo2-1,topo3)) return dp[topo1][topo2][topo3] = 1;
	if (cartas[topo3][3] % 3 == 0 && solve(topo1,topo2,topo3-1)) return dp[topo1][topo2][topo3] = 1;
	if ((cartas[topo1][1] + cartas[topo2][2]) % 3 == 0 && solve(topo1-1,topo2-1,topo3)) return dp[topo1][topo2][topo3] = 1;
	if ((cartas[topo1][1] + cartas[topo3][3]) % 3 == 0 && solve(topo1-1,topo2,topo3-1)) return dp[topo1][topo2][topo3] = 1;
	if ((cartas[topo2][2] + cartas[topo3][3]) % 3 == 0 && solve(topo1,topo2-1,topo3-1)) return dp[topo1][topo2][topo3] = 1;
	if ((cartas[topo1][1] + cartas[topo2][2] + cartas[topo3][3]) % 3 == 0 && solve(topo1-1,topo2-1,topo3-1)) return dp[topo1][topo2][topo3] = 1;
	return dp[topo1][topo2][topo3] = 0;
} 
int main(){
	while(scanf("%d",&n) && n){
		memset(dp,-1,sizeof(dp));
		for(int i=n;i>0;i--){
			for(int j=1;j <= 3;j++){
				scanf("%d",&cartas[i][j]);
			}
		}
		printf("%d\n",solve(n,n,n));
	}
	return 0;
}
