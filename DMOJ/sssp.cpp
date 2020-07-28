// Ivan Carvalho
// Solution to https://dmoj.ca/problem/sssp
#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 100000000
#define MAXN 1001
int matriz[MAXN][MAXN],S[MAXN],processado[MAXN];
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j =1;j<=n;j++){
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
	for(int i=1;i<=n;i++) S[i] = matriz[1][i];
	processado[1] = 0;
	while(true){
		int davez = -1, menor = INF;
		for(int i=1;i<=n;i++){
			if(S[i] < menor && !processado[i]){
				davez = i;
				menor = S[i];
			}
		}
		if(davez == -1) break;
		processado[davez] = 1;
		for(int i=1;i<=n;i++) S[i] = min(S[i],menor + matriz[davez][i]);
	}
	for(int i=1;i<=n;i++){
		if(S[i] == INF) S[i] = -1;
		printf("%d\n",S[i]);
	}
	return 0;
}