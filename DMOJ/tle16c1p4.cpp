// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle16c1p4
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 101
#define INF 100000110
using namespace std;
int matriz[MAXN][MAXN],microondas[MAXN],n,m,k;
int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&microondas[i]);
		for(int j=1;j<=n;j++){
			matriz[i][j] = INF;
		}
		matriz[i][i] = 0;
	}
	while(m--){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		matriz[u][v] = min(matriz[u][v],peso);
		matriz[v][u] = min(matriz[v][u],peso);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				matriz[i][j] = min(matriz[i][j],matriz[i][k] + matriz[k][j]);
			}
		}
	}
	int resp = 0;
	for(int s=1;s<=n;s++){
		for(int u=s+1;u<=n;u++){
			for(int v = u+1;v<=n;v++){
				int qtd = 0;
				for(int i=1;i<=n;i++){
					int dist = min(min(matriz[v][i],matriz[u][i]),matriz[s][i]);
					if(dist<=k) qtd += microondas[i];
				}
				resp = max(resp,qtd);
			}
		}
	}
	printf("%d\n",resp);
	return 0;
}