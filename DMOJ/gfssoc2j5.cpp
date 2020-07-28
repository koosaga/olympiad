// Ivan Carvalho
// Solution to https://dmoj.ca/problem/gfssoc2j5
#include <cstdio>
#define MAXN 500010
int soma[MAXN][11],freq[11];
int main(){
	int n,q;
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10;j++) soma[i][j] = soma[i-1][j];
		int davez;
		scanf("%d",&davez);
		soma[i][davez]++;
		//for(int j=1;j<=10;j++) printf("%d ",soma[i][j]);
		//printf("\n");
	}
	while(q--){
		int a,b;
		scanf("%d %d",&a,&b);
		for(int j=1;j<=10;j++){
			freq[j] = soma[n][j] - (soma[b][j] - soma[a-1][j]);
		}
		for(int j = 10;j >= 1;j--){
			if(freq[j] > 0){
				printf("%d %d\n",j,freq[j]);
				break;
			}
		}
	}
	return 0;
}