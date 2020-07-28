// Ivan Carvalho
// Solution to https://www.spoj.com/problems/HEISLAZY/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAXN 110
using namespace std;
double matriz[MAXN][MAXN],capacidade[MAXN],cordx[MAXN],cordy[MAXN];
int n;
int main(){
	while(scanf("%d %lf %lf %lf %lf",&n,&cordx[0],&cordy[0],&cordx[1],&cordy[1])){
		if(n == -1) break;
		n++;
		for(int i=2;i<=n;i++){
			scanf("%lf %lf %lf",&cordx[i],&cordy[i],&capacidade[i]);
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++){
				double val = hypot(cordx[i] - cordx[j],cordy[i] - cordy[j]);
				matriz[i][j] = min(val, abs(val - capacidade[i]) );
			}
		}
		for(int k=0;k<=n;k++){
			for(int i=0;i<=n;i++){
				for(int j=0;j<=n;j++){
					matriz[i][j] = min(matriz[i][j],matriz[i][k] + matriz[k][j]);
				}
			}
		}
		printf("%.2lf\n",matriz[0][1]);
	}
	return 0;
}