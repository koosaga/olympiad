// Ivan Carvalho
// Solution to https://www.spoj.com/problems/NFACTOR/
#include <cstdio>
const int MAXN = 1e6 + 1;
const int MAXL = 11;
int crivo[MAXN];
int acumulada[MAXN][MAXL];
int main(){
	for(int i=2;i<MAXN;i++){
		if(!crivo[i]){
			crivo[i] = 1;
			for(int j = 2*i;j < MAXN;j+= i){
				crivo[j]++;
			}
		}
	}
	for(int i=1;i<MAXN;i++){
		for(int j=0;j<MAXL;j++) acumulada[i][j] = acumulada[i-1][j];
		acumulada[i][crivo[i]]++;
	}
	int TC;
	scanf("%d",&TC);
	while(TC--){
		int a,b,n;
		scanf("%d %d %d",&a,&b,&n);
		printf("%d\n",acumulada[b][n] - acumulada[a-1][n]);
	}
	return 0;
}