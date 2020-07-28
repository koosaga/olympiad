// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1089
#include <cstdio>
int vetor[100001];
int main(){
	int n;
	while(scanf("%d",&n) && n){
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
		}
		vetor[0] =vetor[n];
		vetor[n+1] = vetor[1];
		int resp = 0;
		for(int i = 1;i<=n;i++){
			resp += int(vetor[i-1] < vetor[i] && vetor[i] > vetor[i+1]);
		}
		printf("%d\n",2*resp);
	}
	return 0;
}
