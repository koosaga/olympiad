// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1798
#include <cstdio>
#include <algorithm>
#define MAXN 200100
using namespace std;
int tamanhos[MAXN],preco[MAXN],tabela[MAXN],objetivo,canos;
int main(){
	scanf("%d %d",&canos,&objetivo);
	for(int i=0;i<canos;i++) scanf("%d %d",&tamanhos[i],&preco[i]);
	for(int i=0;i<canos;i++) {
		for(int j=tamanhos[i];j<=objetivo;j++){
			tabela[j] = max(tabela[j],tabela[j-tamanhos[i]]+preco[i]);
		}
	}
	printf("%d\n",tabela[objetivo]);
	return 0;
}
