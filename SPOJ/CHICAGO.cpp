// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CHICAGO/
#include <cstdio>
#include <algorithm>
#define MAXN 101
using namespace std;
double matriz[MAXN][MAXN];
int n,m;
int main(){
	while(scanf("%d",&n) && n){
		scanf("%d",&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				matriz[i][j] = 0.0;
			}
			matriz[i][i] = 1.0;
		}
		while(m--){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			double prob = double(peso) * 0.01;
			matriz[u][v] = prob;
			matriz[v][u] = prob;
		}
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					matriz[i][j] = max(matriz[i][j],matriz[i][k] * matriz[k][j]);
				}
			}
		}
		matriz[1][n] *= 100.0;
		printf("%.6lf percent\n",matriz[1][n]);
	}
	return 0;
}