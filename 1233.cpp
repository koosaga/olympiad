// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1233
#include <cstdio>
typedef long long ll;
ll phi(ll n){
	double result = n;
	for(ll i=2;i*i<=n;i++){
		if(n % i == 0){
			while(n % i == 0) n /= i;
			result *= (1.0 - (1.0/(double)i));
		}
	}
	if(n != 1) result *= (1.0 - (1.0/(double)n));
	return (ll)result;
}
int main(){
	ll n;
	while(scanf("%lld",&n) != EOF){
		printf("%lld\n",phi(n)/2);
	}
	return 0;
}
