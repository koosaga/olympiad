// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2067
#include <cstdio>
#define MAXN 201
int possivel[MAXN],soma[MAXN][MAXN],n,m;
int main(){
	scanf("%d %d",&n,&m);
	for(int linha=1;linha<=n;linha++){
		for(int coluna = 1;coluna <= m;coluna++){
			int davez;
			scanf("%d",&davez);
			soma[linha][coluna] = soma[linha][coluna-1] + int(davez == 0);
		}
	}
	int minimo = n < m ? n : m;
	for(int tamanho = 1;tamanho <= minimo;tamanho++){
		for(int linha=1;linha + tamanho - 1 <= n && !possivel[tamanho];linha++){
			for(int coluna = 1;coluna + tamanho - 1 <= m && !possivel[tamanho];coluna++){
				int total = 0;
				for(int linhadavez = linha;linhadavez <= linha + tamanho - 1;linhadavez++){
					total += soma[linhadavez][coluna+tamanho-1] - soma[linhadavez][coluna-1];
				}
				if(total == 0){
					possivel[tamanho] = 1;
				}
			}
		}
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int davez;
		scanf("%d",&davez);
		if(possivel[davez]) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
