// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACOINS/
#include <cstdio>
#define MAXN 10001
#define MAXS 100001
int possivel[MAXS],acumulada[MAXS],n,q;
int main(){
	possivel[0] = 1;
	scanf("%d %d",&n,&q);
	while(n--){
		int davez;
		scanf("%d",&davez);
		for(int i = MAXS - 1;i >= davez;i--){
			possivel[i] |= possivel[i - davez];
		}
	}
	for(int i = 1;i < MAXS;i++){
		acumulada[i] = acumulada[i-1] + possivel[i];
	}
	while(q--){
		int a,b;
		scanf("%d %d",&a,&b);
		printf("%d\n",acumulada[b] - acumulada[a-1]);
	}
	return 0;
}