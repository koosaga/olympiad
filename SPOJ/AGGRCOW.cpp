// Ivan Carvalho
// Solution to https://www.spoj.com/problems/AGGRCOW/
#include <cstdio>
#include <algorithm>
#define MAXN 100001
using namespace std;
int posicao[MAXN],n,c;
int valido(int menor){
	int vacas = 1, ultima = posicao[1];
	for(int i=2;i<=n;i++){
		if(posicao[i] - ultima >= menor){
			vacas++;
			if (vacas == c) return 1;
			ultima = posicao[i];
		}
	}
	return 0;
}
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		scanf("%d %d",&n,&c);
		for(int i=1;i<=n;i++) scanf("%d",&posicao[i]);
		sort(posicao+1,posicao+n+1);
		int ini = posicao[1], fim = posicao[n],meio,resposta;
		while(ini <= fim){
			meio = (ini+fim)/2;
			if(valido(meio)){
				resposta = meio;
				ini = meio + 1;
			}
			else{
				fim = meio - 1;
			}
		}
		printf("%d\n",resposta);
	}
	return 0;
}