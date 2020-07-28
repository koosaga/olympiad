// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1099
#include <cstdio>
int main(){
	int casos,caso;
	scanf("%d",&casos);
	for (caso=0;caso<casos;caso++){
		int x,y,resposta=0,i;
		scanf("%d %d",&x,&y);
		if (x>y){
			int tmp = y;
			y = x;
			x = tmp;
		}
		if (x%2==0) x++;
		else x+=2;
		for (i=x;i<y;i+=2) resposta+= i;
		printf("%d\n",resposta);
	}
	return 0;
}
