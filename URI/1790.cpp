// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1790
#include <cstdio>
#define MAXN 51
int matriz[MAXN][MAXN],processado[MAXN],visitados,n,m;
void dfs(int v){
	visitados++;
	processado[v] = 1;
	for(int u=1;u<=n;u++){
		if(matriz[u][v] && !processado[u]) dfs(u);
	}
}
void limpa(){
	for(int i=1;i<=n;i++){
		processado[i] = 0;
	}
	visitados = 0;
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		int resp = 0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				matriz[i][j] = 0;
			}
		}
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			matriz[u][v] = matriz[v][u] = 1;
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(matriz[i][j]){
					matriz[i][j] = matriz[j][i] = 0;
					limpa();
					dfs(1);
					resp += int(visitados != n);
					matriz[i][j] = matriz[j][i] = 1;
				}
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
