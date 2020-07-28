// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco05p1
#include <cstdio>
#include <queue>
#define MAXN 101
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int matriz[MAXN][MAXN],processado[MAXN][MAXN],iteracao,n,m;
inline int valido(int x,int y,int v1,int v2,int v3){
	return x >= 1 && y >= 1 && x <= n && y <= m && processado[x][y] != iteracao && (matriz[x][y] == v1 || matriz[x][y] == v2 || matriz[x][y] == v3);
}
int func(int v1,int v2,int v3){
	iteracao++;
	queue<ii> bfs;
	for(int i=1;i<=m;i++){
		bfs.push(MP(1,i));
	}
	while(!bfs.empty()){
		int x = bfs.front().first;
		int y = bfs.front().second;
		bfs.pop();
		if(processado[x][y] == iteracao) continue;
		processado[x][y] = iteracao;
		if(x == n){
			return 1;
		}
		for(int i=0;i<4;i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(valido(nx,ny,v1,v2,v3)){
				bfs.push(MP(nx,ny));
			}
		}
	}
	return 0;
}
int main(){
	scanf("%d %d",&m,&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&matriz[i][j]);
		}
	}
	for(int i=0;i<=9;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				if(func(i,j,k)){
					printf("%d %d %d\n",i,j,k);
					return 0;
				}
			}
		}
	}
	 printf("-1 -1 -1\n");
	return 0;
}