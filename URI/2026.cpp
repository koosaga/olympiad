// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2026
#include <cstdio>
#define max(A,B) (A>B) ? (A) : (B)
#define MAXW 1100
#define MAXP 110
int tab[MAXP][MAXW],pesos[MAXP],valores[MAXP],p,w;
int knapsack(int obj, int aguenta){
	if (tab[obj][aguenta]!= -1) return tab[obj][aguenta];
	if (obj > p || !aguenta) return tab[obj][aguenta] = 0;
	int nao_coloca = knapsack(obj+1,aguenta);
	if (pesos[obj] <= aguenta){
		int coloca = knapsack(obj+1,aguenta-pesos[obj]) + valores[obj];
		return tab[obj][aguenta] = max(coloca,nao_coloca);
	}
	return tab[obj][aguenta] = nao_coloca;
}
int main(){
	int galhos;
	scanf("%d",&galhos);
	for(int davez = 1;davez<=galhos;davez++){
		printf("Galho %d:\n",davez);
		scanf("%d %d",&p,&w);
		for(int i=0;i<=p+5;i++) for(int j=0;j<=w+10;j++) tab[i][j] = -1;
		for(int i=1;i<=p;i++) scanf("%d %d",&valores[i],&pesos[i]);
		printf("Numero total de enfeites: %d\n\n",knapsack(1,w));
	}
	return 0;
}
