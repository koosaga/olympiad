// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1883
#include <cstdio>
#include <queue>
#define MAXN 1001
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
char matriz[MAXN][MAXN];
int processado[MAXN][MAXN];
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		int n,m,x_e,y_e;
		scanf("%d %d",&n,&m);
		for(int i=0;i<n;i++){
			scanf("%s",matriz[i]);
			for(int j=0;j<m;j++){
				processado[i][j] = 0;
				if(matriz[i][j] == 'E'){
					x_e = i;
					y_e = j;
				}
			}
		}
		queue<iii> bfs;
		int possivel = 0;
		int dist_entrada = n*m + 1;
		bfs.push(MP(0,MP(x_e,y_e)));
		while(!bfs.empty()){
			iii davez = bfs.front();
			bfs.pop();
			int percorrido =  davez.first , x = davez.second.first, y = davez.second.second;
			if(processado[x][y]) continue;
			if(percorrido > dist_entrada) break;
			processado[x][y] = 1;
			if(matriz[x][y] == '#') continue;
			if(matriz[x][y] == 'F'){
				possivel = 0;
				break;
			}
			if(matriz[x][y] == 'S'){
				possivel = 1;
				dist_entrada = percorrido;
				continue;
			}
			if(x-1 >= 0 && !processado[x-1][y]){
				bfs.push(MP(percorrido+1,MP(x-1,y)));
			}
			if(y-1 >= 0 && !processado[x][y-1]){
				bfs.push(MP(percorrido+1,MP(x,y-1)));
			}
			if(x + 1 < n && !processado[x+1][y]){
				bfs.push(MP(percorrido+1,MP(x+1,y)));
			}
			if(y + 1 < m && !processado[x][y+1]){
				bfs.push(MP(percorrido+1,MP(x,y+1)));
			}
		}
		if(possivel) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
