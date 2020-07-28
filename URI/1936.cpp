// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1936
#include <cstdio>
int fatorial(int x){
	if (x == 0 || x == 1) return 1;
	return x * fatorial(x-1);
}
int main(){
	int n,resposta = 0;
	scanf("%d",&n);
	for(int fat = 9; fat > 0; fat--){
		int davez = fatorial(fat);
		resposta += n / davez;
		n %= davez;
	}
	printf("%d\n",resposta);
	return 0;
}
