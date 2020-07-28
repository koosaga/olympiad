// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BYTESM2/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 101
using namespace std;
int dp[MAXN][MAXN],matriz[MAXN][MAXN],n,m,TC;
int solve(int x,int y){
	if(dp[x][y] != -1) return dp[x][y];
	if(x == n){
		return dp[x][y] = matriz[x][y];
	}
	int melhor = solve(x+1,y) + matriz[x][y];
	if(y - 1 >= 1) melhor = max(melhor, matriz[x][y] + solve(x+1,y-1));
	if(y + 1 <= m) melhor = max(melhor,matriz[x][y] + solve(x+1,y+1));
	return dp[x][y] = melhor;
}
int main(){
	scanf("%d",&TC);
	while(TC--){
		memset(dp,-1,sizeof(dp));
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&matriz[i][j]);
			}
		}
		int melhor = -1;
		for(int i=1;i<=m;i++) melhor = max(melhor,solve(1,i));
		printf("%d\n",melhor);
	}
	return 0;
}