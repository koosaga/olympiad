// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1525
#include <cstdio>
#include <deque>
#define MAXN 101
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
char mapa[MAXN][MAXN];
int n,m,k,xini,yini,processado[MAXN][MAXN];
inline int valido(int x,int y){
	return x >= 0 && x < n && y >= 0 && y < m;
}
inline int borda(int x,int y){
	return x == 0 || y == 0 || x == n-1 || y == m-1;
}
int main(){
	while(scanf("%d %d %d",&n,&m,&k) && (n||m||k)){
		for(int i=0;i<n;i++){
			scanf("%s",mapa[i]);
			for(int j=0;j<m;j++){
				processado[i][j] = 0;
				if(mapa[i][j] == 'x'){
					xini = i;
					yini = j;
				}
			}
		}
		deque<iii> bfs;
		bfs.push_front(MP(0,MP(xini,yini)));
		int possivel = 0;
		while(!bfs.empty()){
			iii davez = bfs.front();
			bfs.pop_front();
			int pecorrido = davez.first, x = davez.second.first, y = davez.second.second;
			if(pecorrido > k) break;
			if(processado[x][y]) continue;
			processado[x][y] = 1;
			if(borda(x,y)){
				possivel = 1;
				break;
			}
			if(valido(x+1,y) && !processado[x+1][y]){
				if(mapa[x+1][y] == '^') bfs.push_front(MP(pecorrido,MP(x+1,y)));
				else if(mapa[x+1][y] == 'v') bfs.push_back(MP(pecorrido+1,MP(x+1,y)));
			}
			if(valido(x-1,y) && !processado[x-1][y]){
				if(mapa[x-1][y] == 'v') bfs.push_front(MP(pecorrido,MP(x-1,y)));
				else if(mapa[x-1][y] == '^') bfs.push_back(MP(pecorrido+1,MP(x-1,y)));
			}
			if(valido(x,y+1) && !processado[x][y+1]){
				if(mapa[x][y+1] == '<') bfs.push_front(MP(pecorrido,MP(x,y+1)));
				else if(mapa[x][y+1] == '>') bfs.push_back(MP(pecorrido+1,MP(x,y+1)));
			}
			if(valido(x,y-1) && !processado[x][y-1]){
				if(mapa[x][y-1] == '>') bfs.push_front(MP(pecorrido,MP(x,y-1)));
				else if(mapa[x][y-1] == '<') bfs.push_back(MP(pecorrido+1,MP(x,y-1)));
			}
		}
		if(possivel) printf("Sim\n");
		else printf("Nao\n");
	}
	return 0;
}
