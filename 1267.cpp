// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1267
#include <cstdio>
#define MAXN 500
int vetor[MAXN],n,d;
int main(){
	while(scanf("%d %d",&n,&d) && (n||d)){
		for(int i=1;i<=n;i++){
			vetor[i] = 1;
		}
		for(int j=1;j<=d;j++){
			for(int i=1;i<=n;i++){
				int davez;
				scanf("%d",&davez);
				vetor[i] &= davez;
			}
		}
		int y = 0;
		for(int i=1;i<=n;i++){
			y |= vetor[i];
		}
		if(y) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
