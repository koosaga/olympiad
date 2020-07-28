// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1179
#include <cstdio>
int main(){
	int par[5],impar[5];
	int pares=0,impares=0,i,j;
	for(i=0;i<15;i++){
		int davez;
		scanf("%d",&davez);
		if (davez%2==0){
			par[pares] = davez;
			pares += 1;
		}
		else {
			impar[impares] = davez;
			impares += 1;
		}
		if (pares==5){
			pares = 0;
			for(j=0;j<5;j++){
				printf("par[%d] = %d\n",j,par[j]);
			}
		}
		if (impares==5){
			impares=0;
			for(j=0;j<5;j++){
				printf("impar[%d] = %d\n",j,impar[j]);
			}
		}
	}
	for(i=0;i<impares;i++){
		printf("impar[%d] = %d\n",i,impar[i]);
	}
	for(i=0;i<pares;i++){
		printf("par[%d] = %d\n",i,par[i]);
	}
	return 0;
}
