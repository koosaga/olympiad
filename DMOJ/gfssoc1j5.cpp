// Ivan Carvalho
// Solution to https://dmoj.ca/problem/gfssoc1j5
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 1001
#define INF 100000000
int matriz[MAXN][MAXN];
int main(){
	int n,m,t;
	scanf("%d %d %d",&n,&m,&t);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			matriz[i][j] = INF;
		}
		matriz[i][i] = 0;
	}
	while(m--){
		int a,b;
		scanf("%d %d",&a,&b);
		matriz[a][b] = min(matriz[a][b],t);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				matriz[i][j] = min(matriz[i][j],matriz[i][k] + matriz[k][j]);
			}
		}
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int a,b;
		scanf("%d %d",&a,&b);
		if(matriz[a][b] == INF) printf("Not enough hallways!\n");
		else printf("%d\n",matriz[a][b]);
	}
	return 0;
}