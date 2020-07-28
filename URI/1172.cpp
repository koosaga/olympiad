// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1172
#include <cstdio>
int main(){
	int i;
	for(i=0;i<10;i++){
		int davez;
		scanf("%d",&davez);
		if (davez<=0) printf("X[%d] = 1\n",i);
		else printf("X[%d] = %d\n",i,davez);
	}
	return 0;
}
