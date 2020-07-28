// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c4p6
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5*1e5 + 10;

vector<int> grafo[MAXN];
int dp[MAXN][2],resposta[MAXN],N;

void add(int v,int u){

	int cand = dp[u][0] + 1;
	if(cand > dp[v][0]){
		dp[v][1] = dp[v][0];
		dp[v][0] = cand;
	}
	else if(cand > dp[v][1]){
		dp[v][1] = cand;
	}

}

void dfs1(int v,int p){

	dp[v][0] = dp[v][1] = 1;

	for(int u : grafo[v]){
		if(u == p) continue;
		dfs1(u,v);
		add(v,u);
	}

}

void dfs2(int v,int p){

	resposta[v] = dp[v][0];

	for(int u : grafo[v]){
		if(u == p) continue;
		int copia = dp[v][0];
		int cand = dp[u][0] + 1;
		if(cand == dp[v][0]) dp[v][0] = dp[v][1];
		add(u,v);
		dfs2(u,v);
		dp[v][0] = copia;
	}

}

int main(){

	scanf("%d",&N);
	for(int i = 1;i<N;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[v].push_back(u);
		grafo[u].push_back(v);
	}

	dfs1(1,-1);
	dfs2(1,-1);
	for(int i = 1;i<=N;i++) printf("%d\n",resposta[i]);

	return 0;

}
