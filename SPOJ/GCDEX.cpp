// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GCDEX/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int MAXN = 1e6 + 10;
 
ll G[MAXN];
int isNotPrime[MAXN],phi[MAXN];
 
int main(){
 
	// Initializing
	for(int i = 1;i<MAXN;i++){
		phi[i] = i;
	}
 
	// Calculating phi
	for(int i = 2;i<MAXN;i++){
		if(isNotPrime[i]) continue;
		phi[i]--;
		for(int j = 2*i;j<MAXN;j+=i){
			phi[j] -= phi[j]/i;
			isNotPrime[j] = 1;
		}
	}
 
	// Calculating G
	for(int i = 1;i<MAXN;i++){
		for(int j = 2*i;j<MAXN;j+=i){
			G[j] += 1LL*i*phi[j/i];
		}
	}
 
	for(int i = 2;i<MAXN;i++) G[i] += G[i-1]; // pref sum
 
	int N;
	while(scanf("%d",&N) && N){
		printf("%lld\n",G[N]);
	}
 
	return 0;
 
} 
