// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2044
#include <cstdio>
int main(){
	int n;
	while(scanf("%d",&n) && n > 0){
		int soma = 0;
		int resp = 0;
		while(n--){
			int davez;
			scanf("%d",&davez);
			soma += davez;
			soma %= 100;
			resp += (soma == 0);
		}
		printf("%d\n",resp);
	}
	return 0;
}
