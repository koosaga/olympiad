// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACAROT/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = (ll)1e9 + 7;
inline ll binary_expo(ll base,int expo){
	ll result = 1, pot = base;
	for(int i = 0;(1 << i) <= expo;i++){
		if(expo & (1 << i)) result = (result * pot) % MOD;
		pot = (pot*pot) % MOD;
	}
	return result;
}
int main(){
	int N;
	while(scanf("%d",&N) != EOF){
		ll result = 0,factorial = 1;
		for(int i = 1;i<N;i++){
			ll v1 = binary_expo(i,N - i - 1);
			ll v2 = binary_expo(N - i,i - 1);
			result += (v1 * v2) % MOD;
			result %= MOD;
			factorial = (factorial*i) % MOD;
		}
		factorial *= N;
		factorial %= MOD;
		result *= factorial;
		result %= MOD;
		printf("%lld\n",result);
	}
	return 0;
}