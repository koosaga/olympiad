// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c1p4
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5*1e5 + 10;

bitset<MAXN> block,marcado,flagado;
int vaipara[MAXN],dp[MAXN][2],grau[MAXN],cabeca,corcabeca,N;

int solve(int v,int cor){
	if(dp[v][cor] != -1) return dp[v][cor];
	if(flagado[v] && cor == 1) return dp[v][cor] = 0;
	if(vaipara[v] == cabeca){
		if(cor == 1 && corcabeca == 1) return dp[v][cor] = 0;
		return dp[v][cor] = cor; 
	}
	if(cor == 0){
		return dp[v][cor] = max(solve(vaipara[v],0),solve(vaipara[v],1)) + cor;
	}
	else{
		return dp[v][cor] = solve(vaipara[v],0) + cor;
	}
}

int main(){
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		block.set(i,1);
		scanf("%d",&vaipara[i]);
		grau[vaipara[i]]++;
	}
	vector<int> pilha;
	int ans = 0;
	for(int i = 1;i<=N;i++) if(grau[i] == 0) pilha.push_back(i);
	while(!pilha.empty()){
		int v = (pilha.back());
		pilha.pop_back();
		block[v] = 0;
		if(!flagado[v]){
			ans++;
			flagado[vaipara[v]] = 1;
		}
		int u = vaipara[v];
		grau[u]--;
		if(grau[u] == 0) pilha.push_back(u);
	}
	memset(dp,-1,sizeof(dp));
	for(int i = 1;i<=N;i++){
		if(!block[i] || marcado[i]) continue;
		cabeca = i;
		corcabeca = 0;
		int v1 = solve(i,0);
		int ptr = vaipara[i];
		while(ptr != i){
			marcado[ptr] = 1;
			dp[ptr][0] = dp[ptr][1] = -1;
			ptr = vaipara[ptr];
		}
		marcado[i] = 1;
		dp[i][0] = dp[i][1] = -1;
		corcabeca = 1;
		v1 = max(v1, solve(i,1) );
		ans += v1;
	}
	printf("%d\n",ans);
	return 0;
}