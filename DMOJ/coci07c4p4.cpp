// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c4p4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 501;
const int MAXT = 5002;
int vetor[MAXN];
int dp[MAXN][MAXT],N,T,total,exibir[MAXN];
vector<int> v1,v2;
int solve(int cantor,int tempo){
	if(cantor == N + 1){
		int outro = total - tempo;
		if(outro <= T && tempo <= T) return 1;
		return 0;
	}
	if(tempo > T) return 0;
	if(dp[cantor][tempo] != -1) return dp[cantor][tempo];
	return dp[cantor][tempo] = solve(cantor+1,tempo) | solve(cantor+1,tempo+vetor[cantor]);
}
void prepara(int cantor,int tempo){
	if(cantor == N + 1){
		return;
	}
	if(solve(cantor+1,tempo)){
		v1.push_back(cantor);
		prepara(cantor+1,tempo);
	}
	else{
		v2.push_back(cantor);
		prepara(cantor+1,tempo+vetor[cantor]);
	}
}
int main(){
	scanf("%d %d",&T,&N);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
		total += vetor[i];
	}
	memset(dp,-1,sizeof(dp));
	solve(1,0);
	prepara(1,0);
	int atual = 0;
	for(int i = 0;i<v1.size();i++){
		exibir[v1[i]] = atual;
		atual += vetor[v1[i]];
	}
	atual = 0;
	for(int i = 0;i<v2.size();i++){
		exibir[v2[i]] = atual;
		atual += vetor[v2[i]];
	}
	for(int i = 1;i<=N;i++) printf("%d ",exibir[i]);
	printf("\n");
	return 0;
}