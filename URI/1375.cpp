// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1375
#include <cstdio>
#define MAXN 1001
int vetor[MAXN],A[MAXN],B[MAXN],n;
int main(){
	while(scanf("%d",&n) && n){
		for(int i=1;i<=n;i++){
			scanf("%d %d",&A[i],&B[i]);
			vetor[i] = -1;
		}
		int impossivel = 0;
		for(int i=1;i<=n;i++){
			int novo = i + B[i];
			//printf("I %d N %d\n",i,novo);
			if (novo <= 0 || novo > n){
				impossivel = 1;
				break;
			}
			if(vetor[novo] != -1){
				impossivel = 1;
				break;
			}
			vetor[novo] = A[i];
		}
		if(impossivel){
			printf("-1\n");
		}
		else{
			printf("%d",vetor[1]);
			for(int i=2;i<=n;i++){
				printf(" %d",vetor[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
