// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DCEPCA03/
#include <bits/stdc++.h>
using namespace std;
const long long MAXN = 1e4 + 2;
long long phi[MAXN],resp[MAXN],T,N,somatorio;
int main(){
	for(long long i = 1;i<MAXN;i++){
		phi[i] = i;
	}
	for(long long i = 2;i<MAXN;i++){
		if(phi[i] != i) continue;
		for(long long j = i;j<MAXN;j+=i) phi[j] -= phi[j]/i;
	}
	//for(long long i = 1;i<=100;i++) prlong longf("%lld ",phi[i]);
	//prlong longf("\n");
	for(long long i = 1;i<MAXN;i++){
		resp[i] = resp[i-1] + 2*somatorio*phi[i] + phi[i]*phi[i];
		somatorio += phi[i];
	}
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&N);
		printf("%lld\n",resp[N]);
	}
	return 0;
}