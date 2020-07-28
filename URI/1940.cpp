// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1940
#include <cstdio>
int vetor[600];
int main(){
	int n,m;
	while(scanf("%d %d",&n,&m) != EOF){
		for(int i=1;i<=n;i++){
			vetor[i] = 0;
		}
		for(int j=1;j<=m;j++){
			for(int i=1;i<=n;i++){
				int davez;
				scanf("%d",&davez);
				vetor[i] += davez;
			}
		}
		int resp = 0, exibir = n;
		for(int i=1;i<=n;i++){
			if(vetor[i] >= resp){
				exibir = i;
				resp = vetor[i];
			}
		}
		printf("%d\n",exibir);
	}
	return 0;
}
