// Ivan Carvalho
// Solution to https://dmoj.ca/problem/year2018p3
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
ll N,M,K;
ll V[MAXN],dp[MAXN];
int solve(ll altura){
	memset(dp,0,sizeof(dp));
	ll restam = K;
	for(int i = 1;i<=N;i++){
		ll davez = V[i] + dp[i];
		if(davez >= altura) continue;
		ll delta = altura - davez;
		if(delta > restam) return 0;
		restam -= delta;
		for(int j = i;j <= min(N,i+M-1);j++) dp[j] += delta;
	}
	return 1;
}
int main(){
	cin >> N >> M >> K;
	ll ini,fim,meio,resp = 0;
	for(int i = 1;i<=N;i++){
		cin >> V[i];
	}
	ini = V[1], fim = V[1] + K;
	for(int i = 1;i<=N;i++){
		ini = min(ini,V[i]);
		fim = max(fim,V[i]+K);
	}
	while(ini <= fim){
		ll meio = (ini+fim)/2;
		if(solve(meio)){
			resp = meio;
			ini = meio + 1;
		}
		else{
			fim = meio - 1;
		}
	}
	cout << resp << endl;
	return 0;
}