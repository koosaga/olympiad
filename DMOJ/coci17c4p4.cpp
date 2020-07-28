// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci17c4p4
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;

int N,M,K;
int dp[MAXN][MAXN],somatorio[MAXN][MAXN],proximo[MAXN],vetor[MAXN];

int calcula(int pos,int numero);

int solve(int pos,int numero){
	if(dp[pos][numero] != -1) return dp[pos][numero];
	if(numero == M - 1) return dp[pos][numero] = 0;
	int nxt = proximo[pos];
	int lo = numero + 1;
	int hi = min(numero + K,M);
	int tam = hi - lo + 1;
	int valor = calcula(nxt,lo) - calcula(nxt,hi+1);
	if(vetor[pos] == vetor[nxt]){
		if(valor > 0) return dp[pos][numero] = 1;
		else return dp[pos][numero] = 0;
	}
	else{
		if(valor != tam) return dp[pos][numero] = 1;
		else return dp[pos][numero] = 0;
	}
}

int calcula(int pos,int numero){
	if(numero >= M) return 0;
	if(somatorio[pos][numero] != -1) return somatorio[pos][numero];
	return somatorio[pos][numero] = calcula(pos,numero+1) + solve(pos,numero);
}

int main(){
	memset(dp,-1,sizeof(dp));
	memset(somatorio,-1,sizeof(somatorio));
	scanf("%d %d %d",&N,&M,&K);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
		proximo[i] = i+1;
	}
	proximo[N] = 1;
	for(int i = 1;i<=N;i++){
		printf("%d ",vetor[i]^1^solve(i,0));
	}
	printf("\n");
	return 0;
}