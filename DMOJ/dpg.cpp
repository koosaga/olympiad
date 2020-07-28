// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpg
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

vector<int> grafo[MAXN];
int dp[MAXN],vis[MAXN],N,M;

int solve(int v){

	if(vis[v]) return dp[v];

	vis[v] = 1;
	int best = 0;

	for(int u : grafo[v]){
		best = max(best, solve(u) + 1 );
	}

	return dp[v] = best;

}

int main(){

	scanf("%d %d",&N,&M);
	for(int i = 1;i<=M;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
	}

	int best = 0;
	for(int i = 1;i<=N;i++) best = max(best, solve(i) );
	printf("%d\n",best);

	return 0;

}