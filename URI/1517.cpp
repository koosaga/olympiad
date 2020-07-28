// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1517
#include <cstdio>
#include <algorithm>
#define MAXN 22
#define MAXK 2002
using namespace std;
int dp[MAXN][MAXN][MAXK],macas[MAXN][MAXN][MAXK],n,m,k;
int solve(int x,int y,int t){
	if(x <= 0 || y <= 0 || x > n || y > m || t > 2*k) return 0;
	if(dp[x][y][t] != -1) return dp[x][y][t];
	int retorna = solve(x,y,t+1);
	retorna = max(retorna,solve(x+1,y,t+1));
	retorna = max(retorna,solve(x-1,y,t+1));
	retorna = max(retorna,solve(x,y+1,t+1));
	retorna = max(retorna,solve(x,y-1,t+1));
	retorna = max(retorna,solve(x+1,y+1,t+1));
	retorna = max(retorna,solve(x+1,y-1,t+1));
	retorna = max(retorna,solve(x-1,y+1,t+1));
	retorna = max(retorna,solve(x-1,y-1,t+1));
	return dp[x][y][t] = macas[x][y][t] + retorna;
}
int main(){
	while(scanf("%d %d %d",&n,&m,&k) && (n||m||k)){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int r=0;r<=2*k;r++){
					dp[i][j][r] = -1;
					macas[i][j][r] = 0;
				}
			}
		}
		for(int i=1;i<=k;i++){
			int u,v,tempo;
			scanf("%d %d %d",&u,&v,&tempo);
			macas[u][v][tempo]++;
		}
		int xini,yini;
		scanf("%d %d",&xini,&yini);
		printf("%d\n",solve(xini,yini,0));
	}
	return 0;
}
