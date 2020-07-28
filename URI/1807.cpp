// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1807
#include <cstdio>
typedef long long ll;
ll exp(ll n){
	if (n == 0) return 1;
	if (n % 2 == 1) return (3*exp(n-1))%2147483647;
	ll valor = (exp(n/2))%2147483647;
	valor *= valor;
	valor %= 2147483647;
	return valor;
}
int main(){
	ll entrada;
	scanf("%lld",&entrada);
	printf("%lld\n",exp(entrada));
	return 0;
}
