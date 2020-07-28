// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc16s4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 410;
int soma[MAXN],vetor[MAXN],dp[MAXN][MAXN],resp,n;
int calcula(int ini,int fim){
	return soma[fim] - soma[ini-1];
}
int solve(int ini,int fim){
	if(dp[ini][fim] != -1) return dp[ini][fim];
	if(ini == fim) return dp[ini][fim] = 1;
	for(int quebra = ini;quebra + 1 <= fim;quebra++){
		if(calcula(ini,quebra) == calcula(quebra+1,fim) && solve(ini,quebra) && solve(quebra+1,fim)){
			return dp[ini][fim] = 1;
		}
	}
	for(int quebra = ini;quebra<=fim;quebra++){
		for(int comecaoutro = quebra + 2;comecaoutro <= fim;comecaoutro++){
			if(calcula(ini,quebra) == calcula(comecaoutro,fim) && solve(ini,quebra) && solve(comecaoutro,fim)){
				if(solve(quebra+1,comecaoutro-1)){
					return dp[ini][fim] = 1;
				}
			}
		}
	}
	return dp[ini][fim] = 0;
}
int main(){
	memset(dp,-1,sizeof(dp));
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> vetor[i];
		soma[i] = soma[i-1] + vetor[i];
	}
	for(int i = 1;i<=n;i++){
		for(int j = i;j <= n;j++){
			if(solve(i,j)){
				resp = max(resp, calcula(i,j) );
			}
		}
	}
	cout << resp << endl;
	return 0;
}