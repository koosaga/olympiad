// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2056
#include <cstdio>
#include <queue>
#define MP make_pair
#define MAXN 25
#define F first
#define S second
using namespace std;
typedef pair<int,int> i2;
typedef pair<int,i2> i3;
typedef pair<int,i3> i4;
typedef pair<int,i4> i5;
typedef pair<int,i5> i6;
int dx[5] = {1,-1,0,0};
int dy[5] = {0,0,1,-1};
int processado[MAXN][MAXN][MAXN][MAXN],iteracao,n,m,xs,ys,xb,yb,possivel;
char mapa[MAXN][MAXN];
inline int valido(int x,int y){
	return x >= 0 && x < n && y >= 0 && y < m && mapa[x][y] != '#';
}
int main(){
	while(scanf("%d %d",&n,&m) && (n||m)){
		if(iteracao) printf("\n");
		possivel = 0;
		iteracao++;
		printf("Instancia %d\n",iteracao);
		for(int i=0;i<n;i++){
			scanf("%s",mapa[i]);
			for(int j=0;j<m;j++){
				if(mapa[i][j] == 'S'){
					xs = i;
					ys = j;
				}
				if(mapa[i][j] == 'B'){
					xb = i;
					yb = j;
				}
			}
		}
		priority_queue<i6, vector<i6>, greater<i6> > Dijkstra;
		Dijkstra.push(MP(0,MP(0,MP(xs,MP(ys,MP(xb,yb))))));
		while(!Dijkstra.empty()){
			i6 d = Dijkstra.top();
			Dijkstra.pop();
			int empurros = d.F, movs = d.S.F, x1 = d.S.S.F, y1 = d.S.S.S.F, x2 = d.S.S.S.S.F, y2 = d.S.S.S.S.S;
			if(mapa[x2][y2] == 'T'){
				printf("%d %d\n",movs,empurros);
				possivel = 1;
				break;
			}
			if(processado[x1][y1][x2][y2] == iteracao) continue;
			processado[x1][y1][x2][y2] = iteracao;
			for(int i=0;i<4;i++){
				int nx1 = x1 + dx[i];
				int ny1 = y1 + dy[i];
				if(!valido(nx1,ny1)) continue;
				if(nx1 == x2 && ny1 == y2){
					int nx2 = x2 + dx[i];
					int ny2 = y2 + dy[i];
					if(!valido(nx2,ny2)) continue;
					if(processado[nx1][ny1][nx2][ny2] != iteracao) Dijkstra.push(MP(empurros+1,MP(movs+1,MP(nx1,MP(ny1,MP(nx2,ny2))))));
				}
				else{
					if(processado[nx1][ny1][x2][y2] != iteracao) Dijkstra.push(MP(empurros,MP(movs+1,MP(nx1,MP(ny1,MP(x2,y2))))));
				}
			}
		}
		if(!possivel) printf("Impossivel\n");
	}
	return 0;
}
