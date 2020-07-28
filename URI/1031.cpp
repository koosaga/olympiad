// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1031
#include <cstdio>
#include <deque>
#define MAXN 301
using namespace std;
int dp[MAXN][MAXN],vetor[MAXN];
void solve(int n,int m){
	deque<int> simula;
	for(int i=1;i<=n;i++){
		simula.push_back(i);
	}
	int cortados = 0;
	while(simula.size() != 1){
		int davez = simula.front();
		simula.pop_front();
		if(cortados % m != 0) simula.push_back(davez);
		cortados++;
	}
	dp[n][m] = simula.front();
}
int main(){
	for(int i=1;i<=100;i++){
		for(int j=1;j<MAXN;j++){
			solve(i,j);
			if(dp[i][j] == 13){
				vetor[i] = j;
				break;
			}
		}
	}
	int escolhido;
	while(scanf("%d",&escolhido) && escolhido){
		printf("%d\n",vetor[escolhido]);
	}
	return 0;
}
