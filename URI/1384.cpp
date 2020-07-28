// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1384
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#define MP make_pair
#define LSOne(S) (S & (-S))
#define MAXN 1002
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
const int INF = 1e9;
int buraco[MAXN][MAXN],n,m,w,xi,yi,xf,yf,processado[MAXN][MAXN],dist[MAXN][MAXN];
int dx[24] = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,1,1,1,1,1,2,2,2,2,2};
int dy[24] = {-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,1,2,-2,-1,0,1,2,-2,-1,0,1,2};
int dval[24] = {7,6,5,6,7,6,3,2,3,6,5,2,2,5,6,3,2,3,6,7,6,5,6,7};
inline int valido(int posx,int posy){
	return posx >= 1 && posx <= n && posy >= 1 && posy <= m && !buraco[posx][posy] && !processado[posx][posy];
}
inline int H(int x,int y){
	int v1 = abs(xf - x);
	int v2 = abs(yf - x);
	return 7*max(v1,v2);
}
int main(){
	while(scanf("%d %d",&n,&m) && (n||m)){
		scanf("%d %d %d %d %d",&xi,&yi,&xf,&yf,&w);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				buraco[i][j] = 0;
				processado[i][j] = 0;
				dist[i][j] = INF;
			}
		}
		while(w--){
			int ini,fim,a,b;
			scanf("%d %d %d %d",&ini,&a,&fim,&b);
			for(int i = ini ; i <= fim;i++){
				for(int j=a;j <= b;j++){
					buraco[i][j] = 1;
				}
			}
		}
		int possivel = 0;
		priority_queue<iii, vector<iii>, greater<iii> > Dijkstra;
		dist[xi][yi] = 0;
		Dijkstra.push(MP(0,MP(xi,yi)));
		while(!Dijkstra.empty()){
			iii davez = Dijkstra.top();
			Dijkstra.pop();
			int d = davez.first, x = davez.second.first, y = davez.second.second;
			if(processado[x][y]) continue;
			processado[x][y] = 1;
			if(x == xf && y == yf){
				printf("%d\n",dist[xf][yf]);
				possivel = 1;
				break;
			}
			for(int i=0;i<24;i++){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if(!valido(nx,ny) || dist[nx][ny] <= dist[x][y] + dval[i]) continue; 
				dist[nx][ny] = dist[x][y] + dval[i];
				Dijkstra.push(MP(4*dist[nx][ny] + H(nx,ny),MP(nx,ny)));
			}
		}
		if(!possivel) printf("impossible\n");
	}
	return 0;
}
