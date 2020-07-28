// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2013I/
#include <cstdio>
#include <queue>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
const int MAXR = 501;
const int UBOUND = 1e6 + 1e5;
int matriz[MAXR][MAXR],processado[MAXR][MAXR],iteracao,r,c;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
inline int valido(int x,int y){
	return x >= 1 && x <= r && y >= 1 && y <= c;
}
int func(int altura){
	iteracao++;
	queue<iii> bfs;
	bfs.push(MP(0,MP(1,1)));
	while(!bfs.empty()){
		iii davez = bfs.front();
		bfs.pop();
		int percorrido = davez.first, x = davez.second.first, y = davez.second.second;
		if(processado[x][y] == iteracao) continue;
		processado[x][y] = iteracao;
		if(percorrido + altura >= matriz[x][y]) continue;
		if(x == r && y == c) return 1;
		for(int i=0;i<4;i++){
			int nx = x + dx[i],ny = y + dy[i];
			if(valido(nx,ny) && processado[nx][ny] != iteracao) bfs.push(MP(percorrido+1,MP(nx,ny)));
		}
	}
	return 0;
}
int main(){
	scanf("%d %d",&r,&c);
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			scanf("%d",&matriz[i][j]);
		}
	}
	int ini = 0, fim = UBOUND, meio, resp = -1;
	while(ini <= fim){
		meio = (ini + fim)/2;
		if(func(meio)){
			resp = meio;
			ini = meio + 1;
		}
		else fim = meio - 1;
	}
	printf("%d\n",resp);
	return 0;
}