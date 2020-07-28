// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c6p3
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110;
int matriz[MAXN][MAXN];
int N,M,resp;
int calcula(int x1,int y1,int x2,int y2){
	return matriz[x2][y2] - matriz[x1-1][y2] - matriz[x2][y1-1] + matriz[x1-1][y1-1];
}
int solve(int t1,int t2){
	int ret = M;
	for(int ini = 1, fim = t1;fim <= N;ini++,fim++){
		for(int comeco = 1,termino = t2;termino <= N;comeco++,termino++){
			ret = min(M - calcula(ini,comeco,fim,termino) , ret);
		}
	}
	return ret;
}
int main(){
	scanf("%d %d",&N,&M);
	resp = M;
	for(int i = 1;i<=M;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		matriz[x][y] = 1; 
	}
	for(int i = 1;i<=N;i++){
		for(int j = 1;j <= N;j++){
			matriz[i][j] = matriz[i][j] + matriz[i][j-1] + matriz[i-1][j] - matriz[i-1][j-1];
		}
	}
	for(int i = 1;i <= M;i++){
		if(M % i == 0){
			resp = min(resp, solve(i,M/i) );
		}
	}
	printf("%d\n",resp);
	return 0;
}