// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1450
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 15;
const int MAXL = (1<<15);
int dp[MAXN][MAXL][6],X[MAXN][6],Y[MAXN][6],Z[MAXN][6],n;
int solve(int obj,int bitmask,int estado){
	if(dp[obj][bitmask][estado] != -1) return dp[obj][bitmask][estado];
	int ans = 0;
	for(int prox=0;prox<n;prox++){
		if(prox != obj && !(bitmask & (1 << prox))){
			for(int novoestado = 0;novoestado < 6;novoestado++){
				if(X[obj][estado] >= X[prox][novoestado] && Y[obj][estado] >= Y[prox][novoestado]){
					ans = max(ans,Z[prox][novoestado] + solve(prox,bitmask | (1<<prox),novoestado));
				}
			}
		}
	}
	return dp[obj][bitmask][estado] = ans;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d %d %d",&X[i][0],&Y[i][0],&Z[i][0]);
			X[i][1] = X[i][0];Y[i][1] = Z[i][0];Z[i][1] = Y[i][0];
			X[i][2] = Y[i][0];Y[i][2] = X[i][0];Z[i][2] = Z[i][0];
			X[i][3] = Y[i][0];Y[i][3] = Z[i][0];Z[i][3] = X[i][0];
			X[i][4] = Z[i][0];Y[i][4] = X[i][0];Z[i][4] = Y[i][0];
			X[i][5] = Z[i][0];Y[i][5] = Y[i][0];Z[i][5] = X[i][0];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<(1<<n);j++){
				for(int k=0;k<6;k++){
					dp[i][j][k] = -1;
				}
			}
		}
		int exibir = 0;
		for(int i=0;i<n;i++){
			for(int estado=0;estado<6;estado++){
				exibir = max(exibir,Z[i][estado] + solve(i,(1<<i),estado));
			}
		}
		printf("%d\n",exibir);
	}
	return 0;
}
