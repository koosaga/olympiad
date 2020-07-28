// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1492
#include <cstdio>
typedef unsigned long long llu;
llu log2(llu n){
	llu aux = n;
	llu pot = 0;
	while(aux != 0){
		pot++;
		aux /= 2;
	}
	if((1LLU << pot) == n) return pot;
	return pot - 1;
}
llu conta(llu n){
	if(n <= 0) return 0;
	if(n == 1) return 1;
	llu pot = log2(n);
	llu m = (1LLU << pot) - 1LLU;
	llu soma = pot * (1LLU << (pot - 1));
	soma += n - m;
	return soma + conta(n - m - 1);
}
int main(){
	llu a,b;
	while(scanf("%llu %llu",&a,&b) != EOF){
		printf("%llu\n",conta(b) - conta(a-1));
	}
	return 0;
}
