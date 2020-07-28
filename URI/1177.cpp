// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1177
#include <cstdio>
int main(){
	int i,a,davez=0;
	scanf("%d",&a);
	for(i=0;i<1000;i++){
		davez = davez % a;
		printf("N[%d] = %d\n",i,davez);
		davez++;
	}
	return 0;
}
