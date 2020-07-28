// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1905
#include <cstdio>
#include <cstring>
#define MAXN 7
int matriz[MAXN][MAXN],processado[MAXN][MAXN];
void dfs(int x, int y){
	if (x <= 0 || y <= 0 || x > 5 || y > 5 || matriz[x][y] || processado[x][y]) return;
	processado[x][y] = 1;
	dfs(x+1,y);
	dfs(x-1,y);
	dfs(x,y-1);
	dfs(x,y+1);
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		for(int i=1;i<=5;i++){
			for(int j=1;j<=5;j++){
				scanf("%d",&matriz[i][j]);
			}
		}
		memset(processado,0,sizeof(processado));
		dfs(1,1);
		printf("%s\n",processado[5][5] ? "COPS" : "ROBBERS");
	}
	return 0;
}
