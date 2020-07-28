// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1539
#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 110
#define LIMIT 9999999.0
using namespace std;
double distancias[MAXN][MAXN],coordx[MAXN],coordy[MAXN],raio[MAXN];
int n,m;
int main(){
	while(scanf("%d",&n) && n!=0){
		for(int i=1;i<=n;i++){
			scanf("%lf %lf %lf",&coordx[i],&coordy[i],&raio[i]);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				double distance = sqrt(pow(coordx[i]-coordx[j],2)+pow(coordy[i]-coordy[j],2));
				if (distance<=raio[i]) distancias[i][j]=distance;
				else distancias[i][j]=LIMIT;
			}
		}
		for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) distancias[i][j] = min(distancias[i][j],distancias[i][k]+distancias[k][j]);
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			int a,b;
			scanf("%d %d",&a,&b);
			if (distancias[a][b]==LIMIT) printf("-1\n");
			else printf("%.0lf\n",floor(distancias[a][b]));
		}
	}
	return 0;
}
