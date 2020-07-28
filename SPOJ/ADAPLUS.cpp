// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAPLUS/
#include <cstdio>
#include <algorithm>
#define MAXN 2010
using namespace std;
char entrada[MAXN];
int matriz[MAXN][MAXN],esquerda[MAXN][MAXN],direita[MAXN][MAXN],cima[MAXN][MAXN],baixo[MAXN][MAXN],n,TC;
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",entrada);
			for(int j=1;j<=n;j++){
				matriz[i][j] = (entrada[j-1] == '#');
			}
		}
		int resp = 0;
		for(int i=1;i<=n;i++){
			esquerda[i][1] = matriz[i][1];
			for(int j=2;j<=n;j++){
				esquerda[i][j] = (esquerda[i][j-1] + matriz[i][j])*matriz[i][j];
			}
			direita[i][n] = matriz[i][n];
			for(int j=n-1;j>=1;j--){
				direita[i][j] = (direita[i][j+1] + matriz[i][j])*matriz[i][j];
			}
			cima[1][i] = matriz[1][i];
			for(int j=2;j<=n;j++){
				cima[j][i] = (cima[j-1][i] + matriz[j][i])*matriz[j][i];
			}
			baixo[n][i] = matriz[n][i];
			for(int j=n-1;j>=1;j--){
				baixo[j][i] = (baixo[j+1][i] + matriz[j][i])*matriz[j][i];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int minimo = min(esquerda[i][j],direita[i][j]);
				minimo = min(minimo,cima[i][j]);
				minimo = min(minimo,baixo[i][j]);
				resp = max(resp,minimo);
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}