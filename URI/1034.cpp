// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1034
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LIMIT 9999999
using namespace std;
int tab[1001000],moedas[25];
int main(){
	int casos,valor,numero;
	scanf("%d",&casos);
	while(casos--){
		memset(tab,LIMIT,sizeof(tab));
		scanf("%d %d",&numero,&valor);
		for(int i=0;i<numero;i++) scanf("%d",&moedas[i]);
		tab[0]=0;
		for(int i=0;i<valor;i++){
			for(int j=0;j<numero;j++){
				tab[i+moedas[j]] = min(tab[i+moedas[j]],tab[i]+1);
			}
		}
		printf("%d\n",tab[valor]);
	}
	return 0;
}
