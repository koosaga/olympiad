// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c1p4
#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> trinca;

const int INF = 3000;
const int MAXR = 53;
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};

char entrada[MAXR][MAXR];
int dist_flood[MAXR][MAXR],ok[MAXR][MAXR],dist_source[MAXR][MAXR],x_i,y_i;
int R,C;

inline int valido(int a,int b){
	return min(a,b) >= 0 && a < R && b < C && entrada[a][b] != 'X';
}

int main(){

	scanf("%d %d",&R,&C);

	queue<trinca> bfs;

	for(int i = 0;i<R;i++){
		scanf("%s",entrada[i]);
		for(int j = 0;j<C;j++){
			dist_flood[i][j] = INF;
			if(entrada[i][j] == 'S'){
				x_i = i;
				y_i = j;
			}
			if(entrada[i][j] == '*'){
				bfs.push(make_tuple(0,i,j));
			}
		}
	}

	while(!bfs.empty()){
		trinca davez = bfs.front();
		bfs.pop();
		int x = get<1>(davez),y = get<2>(davez),z = get<0>(davez);
		if(ok[x][y]) continue;
		ok[x][y] = 1;
		if(entrada[x][y] == 'D') continue;
		dist_flood[x][y] = z;
		for(int i = 0;i<4;i++){
			int nx = x + dx[i],ny = y + dy[i];
			if(!valido(nx,ny)) continue;
			bfs.push(make_tuple(z+1,nx,ny));
		}
	}

	memset(ok,0,sizeof(ok));

	bfs.push(make_tuple(0,x_i,y_i));

	while(!bfs.empty()){
		trinca davez = bfs.front();
		bfs.pop();
		int x = get<1>(davez),y = get<2>(davez),z = get<0>(davez);
		if(ok[x][y]) continue;
		ok[x][y] = 1;
		//printf("X %d Y %d Z %d D %d\n",x,y,z,dist_flood[x][y]);
		if(entrada[x][y] == 'D'){
			printf("%d\n",z);
			return 0;
		}
		if(z >= dist_flood[x][y]){
			continue;
		}
		for(int i = 0;i<4;i++){
			int nx = x + dx[i],ny = y + dy[i];
			if(!valido(nx,ny)) continue;
			bfs.push(make_tuple(z+1,nx,ny));
		}
	}

	printf("KAKTUS\n");

	return 0;

}