// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CODESPTB/
#include <cstdio>
#define MAXN 500100
int vetor[MAXN],auxiliar[MAXN];
long long merge_sort(int ini, int fim){
	if (ini==fim) return 0;
	int meio = (ini+fim)/2;
	int direita = meio + 1;
	int tamanho = 0;
	long long inversoes = merge_sort(ini,meio) + merge_sort(direita,fim);
	for(int esquerda=ini;esquerda<=meio;esquerda++){
		while(direita<=fim && vetor[direita]<vetor[esquerda]){
			inversoes += meio - esquerda + 1;
			auxiliar[tamanho++] = vetor[direita++];
		}
		auxiliar[tamanho++] = vetor[esquerda];
	}
	while(direita<=fim) auxiliar[tamanho++] = vetor[direita++];
	for(int i=ini;i<=fim;i++) vetor[i] = auxiliar[i-ini];
	return inversoes;
}
int main(){
	int n,k;
	scanf("%d",&k);
	while(k-- && scanf("%d",&n)){
		for(int i=1;i<=n;i++) scanf("%d",&vetor[i]);
		printf("%lld\n",merge_sort(1,n));
	}
	return 0;
}