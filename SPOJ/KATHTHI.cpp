// Ivan Carvalho
// Solution to https://www.spoj.com/problems/KATHTHI/
#include <cstdio>
#include <deque>
#define MAXN 1010
#define MP make_pair
#define PB push_back
#define PF push_front
#define DIST first
#define X second.first
#define Y second.second
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
char implicito[MAXN][MAXN];
bool visitado[MAXN][MAXN];
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i=0;i<n;i++) scanf("%s",implicito[i]);
		for(int i=0;i<n;i++) for(int j=0;j<m;j++) visitado[i][j] = false;
		deque<iii> bfs;
		bfs.push_back(MP(0,MP(0,0)));
		while(!bfs.empty()){
			iii davez = bfs.front();
			bfs.pop_front();
			int distancia = davez.DIST , x = davez.X, y = davez.Y;
			if (visitado[x][y]) continue;
			visitado[x][y] = true;
			if (x == n-1 && y == m-1){
				printf("%d\n",distancia);
				break;
			}
			if (x - 1 >= 0){
				if (implicito[x][y] == implicito[x-1][y]) bfs.PF(MP(distancia,MP(x-1,y)));
				else bfs.PB(MP(distancia+1,MP(x-1,y)));
			}
			if (x +1 <= n - 1){
				if (implicito[x][y] == implicito[x+1][y]) bfs.PF(MP(distancia,MP(x+1,y)));
				else bfs.PB(MP(distancia+1,MP(x+1,y)));
			}
			if (y - 1 >= 0){
				if (implicito[x][y] == implicito[x][y-1]) bfs.PF(MP(distancia,MP(x,y-1)));
				else bfs.PB(MP(distancia+1,MP(x,y-1)));
			}
			if (y + 1 <= m - 1){
				if (implicito[x][y] == implicito[x][y+1]) bfs.PF(MP(distancia,MP(x,y+1)));
				else bfs.PB(MP(distancia+1,MP(x,y+1)));
			}
		}
	}
	return 0;
}