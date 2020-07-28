// Ivan Carvalho
// Solution to https://www.spoj.com/problems/RIOI_2_3/
#include <cstdio>
#include <cstring>
#include <deque>
#define MAXN 51
#define MAXL 1026
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
int matriz[MAXN][MAXN],visitado[MAXN][MAXN][MAXL],n;
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		memset(visitado,0,sizeof(visitado));
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			for(int j = 0;j < n;j++){
				scanf("%d",&matriz[i][j]);
			}
		}
		int ini_x, fim_x,ini_y,fim_y;
		scanf("%d %d",&ini_x,&ini_y);
		scanf("%d %d",&fim_x,&fim_y);
		deque<iii> bfs;
		bfs.push_back(MP(0,MP(ini_x,ini_y)));
		int exibir = n*n;
		while(!bfs.empty()){
			iii davez = bfs.front();
			bfs.pop_front();
			int oldbitmask = davez.first, x = davez.second.first, y = davez.second.second;
			int bitmask = oldbitmask | (1 << matriz[x][y]);
			if(visitado[x][y][oldbitmask]) continue;
			//printf("%d %d %d\n",x,y,oldbitmask);		
			if (x == fim_x && y == fim_y){
				int resposta = 0;
				for(int i=0;i<=10;i++){
					if(bitmask & (1 << i)) resposta++;
				}
				exibir = min(resposta,exibir);
			}
			visitado[x][y][oldbitmask] = 1;
			if (x + 1 < n && !visitado[x+1][y][bitmask]){
				if(matriz[x][y] == matriz[x+1][y]) bfs.push_front(MP(bitmask,MP(x+1,y)));
				else bfs.push_back(MP(bitmask,MP(x+1,y)));
			}
			if (y + 1 < n && !visitado[x][y+1][bitmask]){
				if(matriz[x][y] == matriz[x][y+1]) bfs.push_front(MP(bitmask,MP(x,y+1)));
				else bfs.push_back(MP(bitmask,MP(x,y+1)));
			}
			if (x - 1 >= 0 && !visitado[x-1][y][bitmask]){
				if(matriz[x][y] == matriz[x-1][y])bfs.push_front(MP(bitmask,MP(x-1,y)));
				else bfs.push_back(MP(bitmask,MP(x-1,y)));
			}
			if (y - 1 >= 0 && !visitado[x][y-1][bitmask]){
				if(matriz[x][y] == matriz[x][y-1]) bfs.push_front(MP(bitmask,MP(x,y-1))); 
				else bfs.push_back(MP(bitmask,MP(x,y-1)));
			}
		}
		printf("%d\n",exibir);
	}
	return 0;
}
 
