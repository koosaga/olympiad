// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1890
#include <cstdio>
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		int x,y,resposta=1;
		scanf("%d %d",&x,&y);
		if (x == 0 && y == 0){
			printf("0\n");
			continue;
		}
		while(x--) resposta *= 26;
		while(y--) resposta *= 10;
		printf("%d\n",resposta);
	}
	return 0;
}
