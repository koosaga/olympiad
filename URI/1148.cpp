// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1148
#include <cstdio>
#include <algorithm>
#define MAXN 550
#define LIMIT 999999999
using namespace std;
int distancias[MAXN][MAXN],visitado[MAXN][MAXN],n,m,q;
void Dijkstra(int S){
	distancias[S][S] = 0;
	visitado[S][S] = 1;
	while(true){
		int davez = -1;
		int menor = LIMIT;
		for(int i=1;i<=n;i++) if (!visitado[S][i] && distancias[S][i]<menor){
			menor = distancias[S][i];
			davez = i;
		}
		if (davez==-1) break;
		visitado[S][davez] = 1;
		for(int i=1;i<=n;i++) distancias[S][i] = min(distancias[S][i],menor+distancias[davez][i]);
	}
}
int main(){
	while(scanf("%d %d",&n,&m) && n!=0){
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
			distancias[i][j]=LIMIT;
			visitado[i][j] = 0;
		}
		for(int i=0;i<m;i++){
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			if (distancias[y][x]!=LIMIT){
				distancias[x][y]=0;
				distancias[y][x]=0;
			}
			else distancias[x][y] = min(distancias[x][y],z);
		}
		scanf("%d",&q);
		while(q--){
			int a,b;
			scanf("%d %d",&a,&b);
			Dijkstra(a);
			if (!visitado[a][b]) printf("Nao e possivel entregar a carta\n");
			else printf("%d\n",distancias[a][b]);
		}
		printf("\n");	
	}
	return 0;
}
