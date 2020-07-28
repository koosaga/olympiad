// Ivan Carvalho
// Solution to https://www.spoj.com/problems/NAGAY1/
#include <bits/stdc++.h>
using namespace std;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
const int MAXN = 510;
typedef tuple<int,int,int> tripla;
typedef pair<int,int> ii;
int xi,yi,xf,yf,n,m;
char entrada[MAXN][MAXN];
int matriz[MAXN][MAXN],processado[MAXN][MAXN];
inline int valido(int x,int y){return x >= 0 && y >= 0 && x < n && y < m && !processado[x][y];}
void precalc(){
	queue<tripla> bfs;
	for(int i = 0;i<n;i++){
		for(int j = 0;j < m;j++){
			if(entrada[i][j] == '+') bfs.push(make_tuple(0,i,j));
		}
	}
	while(!bfs.empty()){
		tripla davez = bfs.front();
		bfs.pop();
		int dist = get<0>(davez),x = get<1>(davez),y = get<2>(davez);
		if(processado[x][y]) continue;
		processado[x][y] = 1;
		matriz[x][y] = dist;
		for(int i = 0;i<4;i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(valido(nx,ny)) bfs.push(make_tuple(dist+1,nx,ny));
		}
	}
}
int func(int val){
	memset(processado,0,sizeof(processado));
	queue<ii> bfs;
	if(matriz[xi][yi] < val) return 0;
	bfs.push(ii(xi,yi));
	while(!bfs.empty()){
		ii davez = bfs.front();
		bfs.pop();
		int x = davez.first,y = davez.second;
		if(processado[x][y]) continue;
		processado[x][y] = 1;
		if(x == xf && y == yf) return 1;
		for(int i = 0;i<4;i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(valido(nx,ny) && matriz[nx][ny] >= val) bfs.push(make_pair(nx,ny));
		}
	}
	return 0;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 0;i<n;i++){
		scanf("%s",entrada[i]);
		for(int j = 0;j < m;j++){
			if(entrada[i][j] == 'V'){
				xi = i;yi = j;
			}
			else if(entrada[i][j] == 'J'){
				xf = i;yf = j;
			}
		}
	}
	precalc();
	int ini = 0,fim = 2*MAXN,resp = -1,meio;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(func(meio)){
			resp = meio;
			ini = meio + 1;
		}
		else{
			fim = meio - 1;
		}
	}
	printf("%d\n",resp);
	return 0;
}