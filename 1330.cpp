// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1330
#include <cstdio>
#include <cstring>
#define MAXN 101
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int matchx[MAXN][MAXN],matchy[MAXN][MAXN],marcado[MAXN][MAXN],n,m,k,iteracao,vis[MAXN][MAXN];
int augmenting_path(int lx,int ly){
	if(vis[lx][ly] == iteracao) return 0;
	vis[lx][ly] = iteracao;
	for(int i=0;i<4;i++){
		int rx = lx + dx[i];
		int ry = ly + dy[i];
		if(rx <= 0 || ry <= 0 || rx > n || ry > m || marcado[rx][ry]) continue;
		if(matchx[rx][ry] == -1 || augmenting_path(matchx[rx][ry],matchy[rx][ry])){
			matchx[rx][ry] = lx;
			matchy[rx][ry] = ly;
			return 1;
		}
	}
	return 0;
}
int main(){
	while(scanf("%d %d",&n,&m) && (n||m)){
		scanf("%d",&k);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				matchx[i][j] = -1;
				matchy[i][j] = -1;
				marcado[i][j] = 0; 
			}
		}
		for(int i=1;i<=k;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			marcado[x][y] = 1;
		}
		int resp = 0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if((i+j) % 2 == 0 && !marcado[i][j]){
					iteracao++;
					resp += augmenting_path(i,j);
				}
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
