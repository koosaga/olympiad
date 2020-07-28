// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1776
#include <cstdio>
typedef long long ll;
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc=1;tc<=TC;tc++){
		ll n;
		scanf("%lld",&n);
		ll resp = 1;
		ll aux = n;
		for(ll i=2;i*i<=n;i++){
			ll pot = 0;
			while(aux % i == 0){
				pot++;
				aux /= i;
			}
			pot++;
			pot /= 2;
			while(pot--) resp *= i;
		}
		if(aux != 1) resp *= aux;
		printf("Caso #%d: %lld\n",tc,resp*resp);
	}
	return 0;
}
