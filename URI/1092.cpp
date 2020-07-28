// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1092
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 610;
int matriz[MAXN][MAXN],indice[MAXN][MAXN],maximocoluna[MAXN],dp[MAXN],resp,N,M;
int main(){
	while(scanf("%d %d",&N,&M) && (N||M)){
		for(int i=1;i<=M;i++) maximocoluna[i] = 1;
		for(int i=1;i<=N;i++){
			scanf("%d",&matriz[i][1]);
			indice[i][1] = 1;
			for(int j= 2;j<=M;j++){
				scanf("%d",&matriz[i][j]);
				if(matriz[i][j] > matriz[i][j-1]){
					indice[i][j] = indice[i][j-1]; 
					maximocoluna[j] = max(maximocoluna[j],j - indice[i][j] + 1); 
				}
				else{
					indice[i][j] = j;
				}
			}
		}
		resp = 0;
		for(int coluna_ini=1;coluna_ini<=M;coluna_ini++){
			for(int coluna_fim = M;coluna_fim>=coluna_ini;coluna_fim--){
				//printf("Ci %d Cf %d\n",coluna_ini,coluna_fim);
				int tam = coluna_fim - coluna_ini + 1;
				if(tam > maximocoluna[coluna_fim]) continue;
				if(tam*M <= resp) continue;
				if(indice[1][coluna_fim] <= coluna_ini){
					dp[1] = 1;
				}
				else{
					dp[1] = 0;
				}
				resp = max(dp[1]*tam,resp);
				for(int linha=2;linha<=N;linha++){
					if(matriz[linha][coluna_ini] > matriz[linha-1][coluna_fim]){
						dp[linha] = dp[linha-1];
					}
					else{
						dp[linha] = 0;
					}
					if(indice[linha][coluna_fim] <= coluna_ini){
						dp[linha]++;
					}
					else{
						dp[linha] = 0;
					}
					resp = max(dp[linha]*tam,resp);
				}
				//for(int i=1;i<=N;i++) printf("%d ",dp[i]);
				//printf("\n");
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
