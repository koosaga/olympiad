// Ivan Carvalho
// Solution to https://dmoj.ca/problem/apio16p1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 501;
const ll MOD = 1e9 + 7;
ll dp[MAXN][MAXN],dp2[MAXN][2*MAXN],somatorio1[MAXN],somatorio2[MAXN];
ll precalc[MAXN],A[MAXN],B[MAXN],N,M;
vector<ll> intervalos;
ll binary_expo(ll val,ll pot){
	if(pot == 0) return 1LL;
	if(pot % 2 == 0){
		ll davez = binary_expo(val,pot/2);
		return (davez*davez) % MOD;
	} 
	return (val*binary_expo(val,pot-1)) % MOD;
}
int main(){
	cin >> N;
	for(int i = 1;i<=N;i++){
		cin >> A[i] >> B[i];
		B[i]++;
		intervalos.push_back(A[i]);
		intervalos.push_back(B[i]); 
	}
	sort(intervalos.begin(),intervalos.end());
	intervalos.erase(unique(intervalos.begin(),intervalos.end()),intervalos.end());
	M = intervalos.size() - 2;
	ll tot = 0;
	for(int v = M;v>=0;v--){
		memset(dp,0,sizeof(dp));
		memset(somatorio2,0,sizeof(somatorio2));
		ll tam = intervalos[v+1] - intervalos[v];
		ll vaiate = min(tam,N);
		for(ll i = 2;i<=vaiate;i++){
			precalc[i] = (tam - i + 1)*binary_expo(i,MOD-2);
			precalc[i] %= MOD;
		}
		for(ll i = N;i>=1;i--){
			if(!(A[i] <= intervalos[v] && intervalos[v+1] <= B[i] )) continue;
			dp[i][1] = 1;
			for(ll j = i+1;j<=N;j++){
				dp[i][1] += somatorio1[j];
			}
			dp[i][1] %= MOD;
			dp[i][1] = (dp[i][1] * tam) % MOD;
			for(ll k = 2;k<=vaiate;k++){
				dp[i][k] = somatorio2[k-1];
			}
			dp2[i][v] = dp[i][1];
			somatorio2[1] += dp[i][1];
			somatorio2[1] %= MOD;
			for(ll k = 2;k<=vaiate;k++){
				dp[i][k] %= MOD;
				dp[i][k] *= precalc[k];
				dp[i][k] %= MOD;
				dp2[i][v] += dp[i][k];
				somatorio2[k] += dp[i][k];
				somatorio2[k] %= MOD;
			}
			dp2[i][v] %= MOD;
			tot += dp2[i][v];
			tot %= MOD;
		}
		for(int i = 1;i<=N;i++){
			somatorio1[i] += dp2[i][v];
			somatorio1[i] %= MOD;
		}
	}
	cout << tot << endl;
	return 0;
}
