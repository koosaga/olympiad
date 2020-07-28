// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci13c1p3
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 51;
int soma[MAXN][MAXN],n,resp,matriz[MAXN][MAXN],copia[MAXN][MAXN];
vector<int> mapa[MAXN][MAXN];
int calcula(int x1,int y1,int x2,int y2){
	return soma[x2][y2] - soma[x1-1][y2] - soma[x2][y1-1] + soma[x1-1][y1 - 1];
}
void precomputa(int x,int y){
	for(int i = x;i <=n;i++){
		for(int j = y;j <= n;j++){
			mapa[x][y].push_back(calcula(x,y,i,j));
		}
	}
	sort(mapa[x][y].begin(),mapa[x][y].end());
}
void termina(int x,int y){
	for(int i = x;i <=n;i++){
		for(int j = y;j <= n;j++){
			int val = calcula(x,y,i,j);
			if(i + 1 <= n && j + 1 <= n){
				vector<int>::iterator it = lower_bound(mapa[i+1][j+1].begin(),mapa[i+1][j+1].end(),val);
				if(it != mapa[i+1][j+1].end() && (*it) == val) resp += upper_bound(mapa[i+1][j+1].begin(),mapa[i+1][j+1].end(),val) - it;
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			scanf("%d",&matriz[i][j]);
			copia[n - i + 1][j] = matriz[i][j];
			soma[i][j] = matriz[i][j] + soma[i-1][j] + soma[i][j-1] - soma[i-1][j-1];
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			precomputa(i,j);
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			termina(i,j);
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			matriz[i][j] = copia[i][j];
			soma[i][j] = matriz[i][j] + soma[i-1][j] + soma[i][j-1] - soma[i-1][j-1];
			mapa[i][j].clear();
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			precomputa(i,j);
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			termina(i,j);
		}
	}
	printf("%d\n",resp);
	return 0;
}