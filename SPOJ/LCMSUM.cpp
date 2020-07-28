// Ivan Carvalho
// Solution to https://www.spoj.com/problems/LCMSUM/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int MAXN = 1000010;
 
ll lcmSum[MAXN],sumOfCoprimes[MAXN];
ll mobius[MAXN],isNotPrime[MAXN];
 
ll fast_sum(ll x){
	return (x*(x+1))/2;
}
 
int main(){
 
	//cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
 
	// Initializing values
	for(int i = 1;i<MAXN;i++){
		mobius[i] = 1;
	}
 
	// Calcuting primes and mobius function
	for(int i = 2;i<MAXN;i++){
		if(isNotPrime[i]) continue;
		mobius[i] *= -1;
		for(int j = 2*i;j<MAXN;j+=i){
			mobius[j] *= -1;
			isNotPrime[j] = 1;
		}
		ll sq = 1LL*i*i;
		for(ll j = sq;j<MAXN;j+=sq) mobius[j] = 0;
	}
 
	// Calculating the sum of coprimes
	for(int i = 1;i<MAXN;i++){
		if(mobius[i] == 0) continue;
		for(int j = i;j<MAXN;j+=i){
			sumOfCoprimes[j] += 
1LL*fast_sum(j/i)*i*mobius[i];
		}
	}
 
	// Calculating the LCM sum
	for(ll i = 1;i<MAXN;i++){
		for(ll j = i;j<MAXN;j+=i){
			lcmSum[j] += j*sumOfCoprimes[j/i];
		}
	}
 
	int TC;
	scanf("%d",&TC);
	for(int i = 1;i<=TC;i++){
		int N;
		scanf("%d",&N);
		printf("%lld\n",lcmSum[N]);
	}
 
	return 0;
 
} 
