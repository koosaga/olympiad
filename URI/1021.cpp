// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1021
#include <cstdio>
int main(){
	int i;
	int notas[6]={100,50,20,10,5,2},moedas[6]={100,50,25,10,5,1};
	double entrada;
	scanf("%lf",&entrada);
	printf("NOTAS:\n");
	for(i=0;i<6;i++){
		int y = (int) entrada/notas[i];
		printf("%d nota(s) de R$ %d.00\n",y,notas[i]);
		entrada -= y*notas[i];
	}
	entrada *= 100;
	printf("MOEDAS:\n");
	for(i=0;i<6;i++){
		int y = (int) entrada/moedas[i];
		printf("%d moeda(s) de R$ %.2lf\n",y,moedas[i]/100.0);
		entrada -= y*moedas[i];
	}
	return 0;
}
