// Ivan Carvalho
// Solution to https://www.spoj.com/problems/JEDNAKOS/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
const int MAXS = 5001;
char entrada[2*MAXN];
int dp[MAXN][MAXS];
int zeromaisadireita[MAXN];
int N,S;
int calcula(int ini,int fim){
	int val = 0;
	int pot = 1;
	if(entrada[ini] == '0') ini = zeromaisadireita[ini];
	for(int i = fim;i>=ini;i--){
		int digito = entrada[i] - '0';
		val += digito*pot;
		pot *= 10;
	}
	return val;
}
int solve(int pos,int resta){
	if(resta < 0) return 1e8;
	if(pos == N){
		if(resta == 0) return 0;
		return 1e8;
	}
	if(dp[pos][resta] != -1) return dp[pos][resta];
	int best = 1e9;
	int comeco = pos;
	if(entrada[pos] == '0') comeco = zeromaisadireita[pos];
	int limite = pos;
	if(entrada[pos] == '0') limite = zeromaisadireita[pos];
	while(limite + 1 < N && calcula(pos,limite+1) <= resta){
		limite++;
	}
	for(int quebra = comeco;quebra<=limite;quebra++){
		best = min(best, solve(quebra+1,resta - calcula(pos,quebra)) );
	}
	return dp[pos][resta] = 1 + best;
}
int main(){
	scanf("%s",entrada);
	N = strlen(entrada);
	int pot = 1;
	while(entrada[N-1] != '='){
		int digito = entrada[N-1] - '0';
		S += digito*pot;
		pot *= 10;
		N--;
	}
	N--;
	for(int i =0;i<N;i++){
		if(entrada[i] != '0') continue;
		zeromaisadireita[i] = i;
		while(zeromaisadireita[i] + 1 < N && entrada[zeromaisadireita[i]+1] == '0'){
			zeromaisadireita[i]++;
		}
	}
	memset(dp,-1,sizeof(dp));
	//printf("%d\n",solve(0,S));
	printf("%d\n",solve(0,S)-1);
	return 0;
}