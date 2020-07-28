// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi13p2
#include <bits/stdc++.h>
#include "artclass.h"
using namespace std;

const int MAXN = 510;
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};
const double averages[4] = {1396298.1629,2777443.2301,6868228.6964,346063.6347};

int matriz[MAXN][MAXN],H,W;
long long somatorio;
double media;

int junta(int r,int g,int b){
	return (r << 16) | (g << 8) | (b); 
}

inline int valido(int a,int b){
	return min(a,b) >= 0 && a < H && b < W; 
}

int calcula(int x,int y){
	int total = 0;
	for(int i = 0;i<4;i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!valido(nx,ny)) continue;
		total += abs(matriz[x][y] - matriz[nx][ny]);
	}
	return total;
}

void roda(){
	for(int i = 0;i<H;i++){
		for(int j = 0;j<W;j++){
			somatorio += calcula(i,j);
		}
	}
}

int style(int h, int w, int R[500][500], int G[500][500], int B[500][500]){

	somatorio = 0;
	media = 0;
	H = h;W = w;

	for(int i = 0;i<H;i++){
		for(int j = 0;j<W;j++){
			matriz[i][j] = junta(R[i][j],G[i][j],B[i][j]);
		}
	}
	roda();

	media = somatorio/double(H*W);	

	double melhor_dist = fabs(media - averages[0]);
	int resp = 0;
	for(int i = 1;i<4;i++){
		if(fabs(media - averages[i]) <= melhor_dist){
			melhor_dist = fabs(media - averages[i]);
			resp = i;
		}
	}

	return resp+1;

}

