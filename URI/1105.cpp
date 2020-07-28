// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1105
#include <cstdio>
int main(){
	int a,b,i;
	while(1){
		scanf("%d %d",&a,&b);
		if (a==0 && b == 0) break;
		int resposta = 1;
		int vetor[a];
		for(i=0;i<a;i++){
			scanf("%d",&vetor[i]);
		}
		for(i=0;i<b;i++){
			int banco1,banco2,debito;
			scanf("%d %d %d",&banco1,&banco2,&debito);
			vetor[banco1-1] -= debito;
			vetor[banco2-1] += debito;
		}
		for(i=0;i<a;i++){
			if (vetor[i]<0){
				resposta = 0;
				break;
			}
		}
		if (resposta) printf("S\n");
		else printf("N\n");
	}
	return 0;
}
