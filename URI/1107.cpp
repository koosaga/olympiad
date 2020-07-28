// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1107
#include <cstdio>
#define MAXN 10010
int vetor[MAXN],a,c,auxiliar[MAXN];
int main(){
	while(scanf("%d %d",&a,&c) &&(a||c)){
		for(int i=1;i<=c;i++){
			scanf("%d",&vetor[i]);
		}
		int resp = a - vetor[1];
		for(int i=2;i<=c;i++){
			if(vetor[i] < vetor[i-1]){
				resp += vetor[i-1] - vetor[i];
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
