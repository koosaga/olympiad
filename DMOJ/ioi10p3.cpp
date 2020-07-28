// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi10p3
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3001;
int matriz[MAXN][MAXN],soma[MAXN][MAXN],R,C,H,W;
int calcula(int x1,int y1,int x2,int y2){
	return soma[x2][y2] - soma[x1-1][y2] - soma[x2][y1 - 1] + soma[x1-1][y1-1];
}
int solve(int mediana){
	for(int i=1;i<=R;i++){
		for(int j=1;j<=C;j++){
			if(matriz[i][j] < mediana) soma[i][j] = -1;
			else if(matriz[i][j] == mediana) soma[i][j] = 0;
			else soma[i][j] = 1;
			soma[i][j] += soma[i][j-1] + soma[i-1][j] - soma[i-1][j-1];
		}
	}
	for(int col1 = 1, col2 = W;col2<=C;col1++,col2++){
		for(int l1 = 1,l2 = H;l2 <= R;l1++,l2++){
			int temp = calcula(l1,col1,l2,col2);
			if(temp < 0){
				return 0;
			}
		}
	}
	return 1;
}
int rectangle(int r,int c,int h,int w,int Q[3001][3001]){
	R = r;
	C = c;
	H = h;
	W = w;
	for(int i=1;i<=R;i++){
		for(int j=1;j<=C;j++){
			matriz[i][j] = Q[i-1][j-1];
		}
	}
	int ini = 1, fim = R*C,resp = -1,meio;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(solve(meio)){
			resp = meio;
			ini = meio + 1;
		}
		else{
			fim = meio - 1;
		}
	}
	return resp;
}

int main(){
    return 0;
}
