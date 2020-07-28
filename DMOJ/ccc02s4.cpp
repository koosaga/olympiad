// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc02s4
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[110];
int nxt[110];
string nomes[110];
int v[110],n,m;
int custo(int ini,int fim){
	int r = 0;
	for(int i=ini;i<=fim;i++) r = max(r,v[i]);
	return r;
}
int solve(int pos){
	if(pos == n + 1){
		return dp[pos] = 0;
	}
	if(dp[pos] != -1) return dp[pos];
	int best = 1e9;
	nxt[pos] = -1;
	for(int quebra = pos;quebra <= pos + m - 1;quebra++){
		int cand = custo(pos,quebra) + solve(quebra + 1);
		if(cand < best){
			best = cand;
			nxt[pos] = quebra;
		}
	}
	return dp[pos] = best;
}
int main(){
	cin >> m >> n;
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++){
		cin >> nomes[i];
		cin >> v[i];
	}
	cout << "Total Time: "  << solve(1) << endl;
	int atual = 1;
	while(atual <= n){
		for(int i = atual;i<=nxt[atual];i++){
			cout << nomes[i] << " ";
		}
		cout << endl;
		atual = nxt[atual] + 1;
	}
	return 0;
}