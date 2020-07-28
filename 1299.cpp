// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1299
#include <cstdio>
#define MAXN 52
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int componente[MAXN*MAXN],matchx[MAXN][MAXN],matchy[MAXN][MAXN],processado[MAXN][MAXN],componentes,marcado[MAXN][MAXN],n,m,meucomponente[MAXN][MAXN],iteracao;
char mapa[MAXN][MAXN];
inline int valido(int x,int y){
	return x >= 0 && x < n && y >= 0 && y < m && !marcado[x][y]; 
}
void dfs(int x,int y){
	processado[x][y] = iteracao;
	meucomponente[x][y] = componentes;
	componente[componentes]++;
	for(int i=0;i<4;i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(valido(nx,ny) && processado[nx][ny] != iteracao) dfs(nx,ny);
	}
}
int augmenting_path(int lx,int ly){
	if(processado[lx][ly] == iteracao) return 0;
	processado[lx][ly] = iteracao;
	for(int i=0;i<4;i++){
		int rx = lx + dx[i], ry = ly + dy[i];
		if(!valido(rx,ry)) continue;
		if(matchx[rx][ry] == -1 || augmenting_path(matchx[rx][ry],matchy[rx][ry])){
			matchx[rx][ry] = lx;
			matchy[rx][ry] = ly;
			return 1;
		}
	}
	return 0;
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		for(int i=0;i<componentes;i++){
			componente[i] = 0;
		}
		componentes = 0;
		iteracao = 0;
		for(int i=0;i<n;i++){
			scanf("%s",mapa[i]);
			for(int j=0;j<m;j++){
				processado[i][j] = 0;
				marcado[i][j] = (mapa[i][j] == 'X');
				matchx[i][j] = -1;
				matchy[i][j] = -1;
				meucomponente[i][j] = 0;
			}
		}
		iteracao++;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(processado[i][j] != iteracao && !marcado[i][j]){
					dfs(i,j);
					componentes++;
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if((i+j)%2 == 0 && !marcado[i][j]){
					//printf("X %d Y %d do comp %d\n",i,j,meucomponente[i][j]);
					iteracao++;
					componente[meucomponente[i][j]] -= 2*augmenting_path(i,j);
				}
			}
		}
		int primeiro = 0;
		for(int i=0;i<componentes;i++){
			if(componente[i]){
				//printf("Componente %d: %d\n",i,componente[i]);
				primeiro = 1;
			}
		}
		if(primeiro) printf("1\n");
		else printf("2\n");
		//for(int i=0;i<n;i++){
		//	for(int j=0;j<m;j++){
		//		if((i+j)%2 == 1 && !marcado[i][j])printf("Match[%d][%d] do Componente %d = (%d,%d)\n",i,j,meucomponente[i][j],matchx[i][j],matchy[i][j]);
		//	}
		//}
	}
	return 0;
}
