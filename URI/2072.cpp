// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2072
#include <cstdio>
#include <map>
#include <algorithm>
#define MP make_pair
#define MAXN 51
using namespace std;
typedef pair<int,int> i2;
typedef pair<int,i2> i3;
map<i3,int> mapa;
int X[MAXN],Y[MAXN],Z[MAXN],peso[MAXN],TC,n,contador;
int crossx[MAXN][MAXN][MAXN],crossy[MAXN][MAXN][MAXN],crossz[MAXN][MAXN][MAXN];
void precalcula(int A, int B, int C){
	int xac = X[C] - X[A],yac = Y[C] - Y[A],zac = Z[C] - Z[A];
	int xab = X[B] - X[A],yab = Y[B] - Y[A],zab = Z[B] - Z[A];
	crossx[A][B][C] = yab*zac - zab*yac;
	crossy[A][B][C] = zab*xac - zac*xab;
	crossz[A][B][C] = xab*yac - xac*yab;
}
int produto(int A, int B, int C, int D){
	int xad = X[D] - X[A], yad = Y[D] - Y[A],zad = Z[D] - Z[A];
	return crossx[A][B][C] * xad + crossy[A][B][C]*yad + crossz[A][B][C] * zad;
}
int main(){
	scanf("%d",&TC);
	while(TC--){
		mapa.clear();
		contador = 0;
		scanf("%d",&n);
		int resp = 0;
		for(int i=1;i<=n;i++){
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			if(!mapa.count(MP(x,MP(y,z)))){
				//printf("OI\n");
				peso[++contador] = 1;
				mapa[MP(x,MP(y,z))] = contador;
				X[contador] = x;
				Y[contador] = y;
				Z[contador] = z;
			}
			else{
				peso[mapa[MP(x,MP(y,z))]]++;
			}
		}
		for(int i=1;i<=contador;i++){
			for(int j=1;j<=contador;j++){
				for(int k=1;k<=contador;k++){
					precalcula(i,j,k);
				}
			}
		}
		for(int i=1;i<=contador;i++){
			resp = max(resp,peso[i]);
			for(int j=i+1;j<=contador;j++){
				resp = max(resp,peso[i]+peso[j]);
				for(int k = j+1;k<=contador;k++){
					resp = max(resp,peso[i]+peso[j]+peso[k]);
					bool flag = crossx[i][j][k] == 0 && crossy[i][j][k] == 0 && crossz[i][j][k] == 0;
					//printf("%d %d %d %d\n",i,j,k,int(flag));
					//printf("%d %d %d\n",crossx[i][j][k],crossy[i][j][k],crossz[i][j][k]);
					int temp = 0;
					for(int r = 1;r<=contador;r++){
						if(!flag){
							if(produto(i,j,k,r) == 0) temp += peso[r];
						}
						else{
							bool novaflag = crossx[i][j][r] == crossx[i][k][r] && crossy[i][j][r] == crossy[i][k][r] && crossz[i][j][r] == crossz[i][k][r];
							temp += peso[r] * int(novaflag);
						}
					}
					resp = max(resp,temp);
				}
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
