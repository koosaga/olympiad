// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c1p5
#include <cstdio>
#include <algorithm>
#define MAXN 251
using namespace std;
int soma[MAXN][MAXN],M,N,A,resp,marcado[MAXN][MAXN];
inline int query(int x1,int x2,int y1,int y2){
	return soma[x2][y2] - soma[x1-1][y2] - soma[x2][y1-1] + soma[x1-1][y1-1];
}
inline void brute(int R,int C){
	if(R == 0 || C == 0) return;
	R = min(N,R);
	C = min(M,C);
	if(marcado[R][C]) return;
	marcado[R][C] = 1;
	for(int i = 1;i + R - 1 <= N;i++){
		for(int j=1;j + C - 1 <= M;j++){
			resp = max(resp, query(i,i + R - 1,j,j + C - 1) );
		}
	}
}
int main(){
	scanf("%d %d %d",&M,&N,&A);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			scanf("%d",&soma[i][j]);
			soma[i][j] += soma[i][j-1] + soma[i-1][j] - soma[i-1][j-1];
		}
	}
	for(int i=1;i<=N;i++){
		brute(i,A/i);
	}
	for(int i=1;i<=M;i++){
		brute(A/i,i);
	}
	printf("%d\n",resp);
	return 0;
}