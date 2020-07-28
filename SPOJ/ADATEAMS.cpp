// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADATEAMS/
#include <cstdio>
typedef long long ll;
const ll MAXN = 1e6 + 1;
const ll MODULO = 1e9 + 7;
ll fatorial[MAXN];
ll fast_expo(ll base,ll expo){
	if(expo == 0) return 1L;
	if(expo == 1) return base % MODULO;
	if(expo % 2 == 0){
		ll temp = fast_expo(base,expo/2);
		return (temp*temp)%MODULO;
	}
	return (base * fast_expo(base,expo-1))%MODULO;
}
ll inv(ll val){
	return fast_expo(val,MODULO-2);
}
ll binomial(ll n,ll k){
	ll cima = fatorial[n];
	ll baixo = inv((fatorial[n - k] * fatorial[k]) % MODULO);
	return (baixo * cima) % MODULO; 
}
int main(){
	fatorial[0] = 1;
	for(ll i = 1;i < MAXN;i++){
		fatorial[i] = (fatorial[i-1]*i) % MODULO;
	}
	ll a,b,c,d;
	while(scanf("%lld %lld %lld %lld",&a,&b,&c,&d) != EOF){
		printf("%lld\n",(binomial(a,b) * fast_expo(binomial(c,d),b)) % MODULO);
	}
	return 0;
}