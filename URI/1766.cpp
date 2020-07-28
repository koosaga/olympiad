// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1766
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAXN 1010
#define MAXL 110
using namespace std;
int renas[MAXN],pesos[MAXN],idades[MAXN];
double alturas[MAXN];
char nomes[MAXN][MAXL];
bool compara(int x, int y){
	if (pesos[x]>pesos[y]) return true;
	if (pesos[x]<pesos[y]) return false;
	if (idades[x]<idades[y]) return true;
	if (idades[x]>idades[y]) return false;
	if (alturas[x]<alturas[y]) return true;
	if (strcmp(nomes[x],nomes[y])<0) return true;
	return false;
}
int main(){
	int casos_no_total,caso_da_vez,renas_total,renas_treno,rena_da_vez;
	scanf("%d",&casos_no_total);
	for (caso_da_vez=1;caso_da_vez<=casos_no_total;caso_da_vez++){
		printf("CENARIO {%d}\n",caso_da_vez);
		scanf("%d %d",&renas_total,&renas_treno);
		for(rena_da_vez=1;rena_da_vez<=renas_total;rena_da_vez++){
			renas[rena_da_vez] = rena_da_vez;
			scanf("%s %d %d %lf",nomes[rena_da_vez],&pesos[rena_da_vez],&idades[rena_da_vez],&alturas[rena_da_vez]);
		}
		sort(renas+1,renas+renas_total+1,compara);
		for(rena_da_vez=1;rena_da_vez<=renas_treno;rena_da_vez++){
			printf("%d - %s\n",rena_da_vez,nomes[renas[rena_da_vez]]);
		}
	}
	return 0;
}
