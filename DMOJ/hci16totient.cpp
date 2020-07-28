// Ivan Carvalho
// Solution to https://dmoj.ca/problem/hci16totient
#include <cstdio>
typedef long long ll;
const ll MOD = 1e9 + 7;
ll totient[1000010],pot[1000010];
int main(){
	ll n,resp = 0;
	totient[1] = 1;
	totient[0] = 0;
	pot[0] = 0;
	pot[1] = 1;
	scanf("%lld",&n);
	for(ll i=2;i<=n;i++){
		totient[i] = i;
	}
	for(ll i = 2;i <= 1001;i++){
		for(ll j = i*i;j<=n;j *= i){
			pot[j] = 1;
		}
	}
	for(ll i=2;i<=n;i++){
		if(totient[i] != i) continue;
		for(ll j = i;j<=n;j+=i) totient[j] -= totient[j]/i;
	}
	for(ll j=0;j<=n;j++){
		resp += pot[totient[j]]*totient[j];
		resp %= MOD;
	}
	printf("%lld\n",resp);
	return 0;
}