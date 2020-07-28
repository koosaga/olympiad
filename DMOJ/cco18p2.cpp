// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco18p2
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;

int matriz[MAXN][MAXN];

int main(){
	int N = 100;
	int x = 1,y = 1,sx = 0,sy = 0,vez = 0;
	for(int i = 1;i<=N;i++){
		for(int j = i+1;j<=N;j++){
			matriz[i][j] = 1;
		}
	}
	for(int i = 2;i<=N;i++){
		if(i <= 4){
			if(sx + matriz[x][i] < sy + matriz[y][i]){
				sx = sx + matriz[x][i];
				x = i;
			}
			else{
				sy = sy + matriz[y][i];
				y = i;
			}
		}	
		else{
			if(vez == 0){
				matriz[x][i] = 100;
				matriz[y][i] = 100;
				vez = 1;
			}
			else{
				matriz[y][i] = 100;
				vez = 0;
			}
			if(sx + matriz[x][i] < sy + matriz[y][i]){
				sx = sx + matriz[x][i];
				x = i;
			}
			else{
				sy = sy + matriz[y][i];
				y = i;
			}
		}
	}
	printf("%d\n",N);
	for(int i = 1;i<N;i++){
		for(int j = i+1;j<=N;j++) printf("%d ",matriz[i][j]);
		printf("\n");
	}
	return 0;
}