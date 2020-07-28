// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2069
#include <cstdio>
typedef long long ll;
ll gcd(ll a,ll b){
	if(a < b){
		ll temp = b;
		b = a;
		a = temp;
	}
	if(b == 0) return a;
	return gcd(b,a%b);
}
int main(){
	ll a,b;
	scanf("%lld %lld",&a,&b);
	ll c = gcd(a,b);
	ll aux = c;
	ll resp = 1;
	for(ll i=2;i*i<=c && aux != 1;i++){
		ll pot = 0;
		while(aux % i == 0){
			aux /= i;
			pot++;
		}
		pot++;
		pot /= 2;
		while(pot--) resp *= i;
	}
	if(aux != 1) resp *= aux;
	printf("%lld\n",resp);
	return 0;
}
