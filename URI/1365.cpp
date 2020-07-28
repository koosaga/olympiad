// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1365
#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;
#define MAXN 301
int soma[MAXN][MAXN],r,c,k;
int main(){
	while(scanf("%d %d %d",&r,&c,&k) && (r||c||k)){
		for(int linha = 1;linha <= r;linha++){
			for(int coluna = 1;coluna <= c;coluna++){
				char davez;
				scanf(" %c",&davez);
				//printf("%c",davez);
				soma[linha][coluna] = soma[linha][coluna-1] + (davez == '.');
			}
			//printf("\n");
		}
		int resp = r*c + MAXN;
		for(int colunaini = 1;colunaini <= c;colunaini++){
			for(int colunafim = colunaini;colunafim <= c;colunafim++){
				if((colunafim - colunaini +1)*r < k) continue;
				int acumulado = 0;
				deque<int> janela;
				for(int linha = 1;linha <= r;linha++){
					janela.push_back(soma[linha][colunafim] - soma[linha][colunaini - 1]);
					acumulado += janela.back();
					while(acumulado >= k){
						int custo = (colunafim - colunaini +1)*janela.size();
						resp = min(resp,custo);
						acumulado -= janela.front();
						janela.pop_front();
					}
				}
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
