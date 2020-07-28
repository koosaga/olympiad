// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1829
#include <cstdio>
#include <cmath>
#define MAXVAL 10001
double vetor[MAXVAL];
int A[MAXVAL],B[MAXVAL],C[MAXVAL];
int main(){
	vetor[2] = log10(2);
	for(int i=3;i<MAXVAL;i++){
		vetor[i] = vetor[i-1] + log10(i);
	}
	int n;
	scanf("%d",&n);
	int lucas = 0;
	int pedro = 0;
	for(int i=1;i<=n;i++){
		scanf("%d %*c %d %d %*c",&A[i],&B[i],&C[i]);
		if(B[i]*log10(A[i]) > vetor[C[i]]){
			lucas++;
		}
		else{
			pedro++;
		}
	}
	if(lucas > pedro){
		printf("Campeao: Lucas!\n");
	}
	else if(pedro > lucas){
		printf("Campeao: Pedro!\n");
	}
	else printf("A competicao terminou empatada!\n");
	for(int i=1;i<=n;i++){
		if(B[i]*log10(A[i]) > vetor[C[i]]){
			printf("Rodada #%d: Lucas foi o vencedor\n",i);
		}
		else{
			printf("Rodada #%d: Pedro foi o vencedor\n",i);
		}
	}
	return 0;
}
