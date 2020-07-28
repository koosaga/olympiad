// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PERMUT2/
#include <cstdio>
int vetor[100010];
int main(){
	int n;
	while(scanf("%d",&n) && n){
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
		}
		int ambiguo = 1;
		for(int i=1;i<=n;i++){
			if(vetor[vetor[i]] != i){
				ambiguo = 0;
				break;
			}
		}
		printf("%s\n",ambiguo ? "ambiguous" : "not ambiguous");
	}
	return 0;
}