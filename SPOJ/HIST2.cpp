// Ivan Carvalho
// Solution to https://www.spoj.com/problems/HIST2/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 15 + 1;
const int MAXL = (1 << 15) + 3;
int dp[MAXN][MAXL],N,vetor[MAXN],alvo;
ll calc[MAXN][MAXL];
int solve(int idx,int bitmask){
	if(bitmask == alvo){
		return dp[idx][bitmask] = vetor[idx];
	}
	if(dp[idx][bitmask] != -1) return dp[idx][bitmask];
	int add = (__builtin_popcount(bitmask) == 1) ? vetor[idx] : 0;
	int melhor = 0;
	for(int prox = 0;prox<N;prox++){
		if(bitmask & (1 << prox)) continue;
		melhor = max(melhor, solve(prox, bitmask | (1 << prox) ) + abs(vetor[idx] - vetor[prox]) );
	}
	return dp[idx][bitmask] = melhor + add;
}
ll count(int idx,int bitmask){
	if(bitmask == alvo){
		return 1LL;
	}
	if(calc[idx][bitmask] != -1) return calc[idx][bitmask];
	int add = (__builtin_popcount(bitmask) == 1) ? vetor[idx] : 0;
	int melhor = solve(idx,bitmask);
	ll ret = 0;
	for(int prox = 0;prox<N;prox++){
		if(bitmask & (1 << prox)) continue;
		if(solve(prox, bitmask | (1 << prox) ) + abs(vetor[idx] - vetor[prox]) + add == melhor) ret += count(prox, bitmask | (1 << prox) );
	}
	return calc[idx][bitmask] = ret;
}
int main(){
	while(cin >> N && N){
		memset(dp,-1,sizeof(dp));
		memset(calc,-1,sizeof(calc));
		alvo = (1 << N) - 1;
		for(int i = 0;i<N;i++) cin >> vetor[i];
		int best = 0;
		ll exibe = 0;
		for(int i = 0;i<N;i++) best = max(best, solve(i, (1 << i) ) );
		for(int i = 0;i<N;i++){
			if(best == solve(i, 1 << i )) exibe += count(i, (1 << i) );
		}
		printf("%d %lld\n",best + 2*N,exibe);
	}
	return 0;
}