// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;

vector<int> grafo[MAXN];
ll dp[MAXN][2];
int N;

ll solve(int v,int c,int p){

	if(dp[v][c] != -1) return dp[v][c];

	ll tot = 1;
	for(int u : grafo[v]){
		if(u == p) continue;
		if(c == 0) tot = (tot * (solve(u,0,v) + solve(u,1,v))) % MOD;
		else tot = (tot * solve(u,0,v)) % MOD;
	}

	return dp[v][c] = tot;

}

int main(){

	memset(dp,-1,sizeof(dp));

	scanf("%d",&N);
	for(int i = 1;i<N;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	printf("%lld\n", (solve(1,0,-1) + solve(1,1,-1)) % MOD );

	return 0;

}