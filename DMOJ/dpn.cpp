// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpn
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 410;
const ll INF = 1e14;

ll dp[MAXN][MAXN],V[MAXN],pref[MAXN];
int N;

ll calc(ll a,ll b){
	if(a > b) return INF;
	return pref[b] - pref[a-1];
}

ll solve(int ini,int fim){
	if(dp[ini][fim] != -1) return dp[ini][fim];
	if(ini == fim) return dp[ini][fim] = 0;
	if(ini + 1 == fim) return dp[ini][fim] = V[ini] + V[fim];

	ll best = INF;

	for(int i = ini;i<fim;i++){
		ll cand = solve(ini,i) + solve(i+1,fim) + calc(ini,fim);
		best = min(best,cand);
	}

	return dp[ini][fim] = best;

}

int main(){

	memset(dp,-1,sizeof(dp));

	cin >> N;
	for(int i = 1;i<=N;i++) cin >> V[i];

	for(int i = 1;i<=N;i++) pref[i] = pref[i-1] + V[i];

	cout << solve(1,N) << endl;

	return 0;

}