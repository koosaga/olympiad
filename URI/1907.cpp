// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1907
#include <cstdio>
#define MAXN 1030
int n,m,resposta;
char grafo[MAXN][MAXN];
bool visitado[MAXN][MAXN];
void dfs(int x, int y){
	if (x < 0 || x >= n || y < 0 || y >= m || grafo[x][y]=='o' || visitado[x][y]) return;
	visitado[x][y] = true;
	dfs(x-1,y);
	dfs(x+1,y);
	dfs(x,y-1);
	dfs(x,y+1);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++) scanf("%s",grafo[i]);
	for(int i=0;i<n;i++) for(int j=0;j<m;j++){
		if (grafo[i][j]=='.' && !visitado[i][j]){
			dfs(i,j);
			resposta++;
		}
	}
	printf("%d\n",resposta);
	return 0;
}
