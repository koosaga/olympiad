// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1376
#include <cstdio>
#define MAXN 101
int r,c,n,k,matriz[MAXN][MAXN],novamatriz[MAXN][MAXN];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
inline int valido(int x,int y){
	return x >= 0 && y >= 0 && x < r && y < c;
}
void func(){
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			novamatriz[i][j] = matriz[i][j];		
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			for(int p=0;p<4;p++){
				int x = i + dx[p];
				int y = j + dy[p];
				if(valido(x,y) && (matriz[i][j] + 1) % n == matriz[x][y] ){
					novamatriz[x][y] = matriz[i][j];
				}
			}
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			matriz[i][j] = novamatriz[i][j];		
		}
	}
}
int main(){
	while(scanf("%d %d %d %d",&n,&r,&c,&k) && (n||r||c||k)){
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				scanf("%d",&matriz[i][j]);
			}
		}
		while(k--) func();
		for(int i=0;i<r;i++){
			printf("%d",matriz[i][0]);
			for(int j=1;j<c;j++){
				printf(" %d",matriz[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
