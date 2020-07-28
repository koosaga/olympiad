// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1381
#include <cstdio>
#define MODULO 1300031LL
#define MAXN 2000010
typedef long long ll;
ll fatorial[MAXN];
ll fast_expo(ll base,ll expo){
	if(expo == 0) return 1LL;
	if(expo == 1) return base;
	if(expo % 2 == 0){
		ll temp = fast_expo(base,expo/2);
		return (temp*temp) % MODULO;
	}
	return (base*(fast_expo(base,expo-1))) % MODULO;
}
ll binomial(ll n,ll k){
	ll a = fatorial[n];
	ll b = (fatorial[k]*fatorial[n-k]) % MODULO;
	ll inv = fast_expo(b,MODULO-2);
	return (a*inv) % MODULO;
}
int main(){
	fatorial[0] = 1;
	for(int i=1;i<MAXN;i++){
		fatorial[i] = ((i%MODULO) *  fatorial[i-1]) % MODULO;
	}
	ll TC;
	scanf("%lld",&TC);
	while(TC--){
		ll n,c;
		scanf("%lld %lld",&n,&c);
		printf("%lld\n",binomial(n+c-1,c));
	}
	return 0;
}
