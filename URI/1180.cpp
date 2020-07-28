// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1180
#include <cstdio>
int main(){
	int a,i,resp=0,pos=0;
	scanf("%d",&a);
	scanf("%d",&resp);
	for(i=1;i<a;i++){
		int davez;
		scanf("%d",&davez);
		if (davez<resp){
			pos = i;
			resp = davez;
		}
	}
	printf("Menor valor: %d\nPosicao: %d\n",resp,pos);
	return 0;
}
