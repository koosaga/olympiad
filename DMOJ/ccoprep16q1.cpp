// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep16q1
#include <cstdio>
#include <algorithm>
using namespace std;
int matriz[1001][1001],resp,TC;
int main(){
	scanf("%d",&TC);
	while(TC--){
		int n,m;
		resp = 0;
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char c;
				scanf(" %c",&c);
				matriz[i][j] = matriz[i][j-1] + (c == 'R'); 
			}
		}
		for(int coluna_ini = 1;coluna_ini<=m;coluna_ini++){
			for(int coluna_fim = m;coluna_fim >= coluna_ini;coluna_fim--){
				if((coluna_fim - coluna_ini + 1)*n <= resp) continue;
				int best = 0, atual = 0;
				for(int linha = 1;linha<=n;linha++){
					if(matriz[linha][coluna_fim] - matriz[linha][coluna_ini-1] == 0){
						atual++;
						best = max(best,atual);
					}
					else{
						atual = 0;
					}
				}
				resp = max(resp, best*(coluna_fim - coluna_ini + 1) );
			}
		}
		printf("%d\n",3*resp);
	}
	return 0;
}