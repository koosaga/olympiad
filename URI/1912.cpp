// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1912
#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAXN 100010
#define EPS 1e-6
using namespace std;
double altura[MAXN];
int main(){
	int n,a;
	while(scanf("%d %d",&n,&a) && (n || a)){
		double objetivo = a,total = 0.0;
		double ini = 0.0, fim = 0.0, meio, resp;
		for(int i=1;i<=n;i++){
			scanf("%lf",&altura[i]);
			fim = max(altura[i],fim);
			total += altura[i];
		}
		if(total + EPS <= objetivo){
			printf("-.-\n");
			continue;
		}
		if(fabs(total - objetivo) < EPS){
			printf(":D\n");
			continue;
		}
		while(fim - ini > EPS){
			meio = (ini+fim)/2.0;
			double temp = 0.0;
			for(int i=1;i<=n;i++){
				if(altura[i] > meio + EPS){
					temp += altura[i] - meio;
				}
			}
			//printf("INI %.4lf MEIO %.4lf FIM %.4lf\n TEMP %.4lf\n",ini,meio,fim,temp);
			if(temp > objetivo + EPS){
				resp = meio;
				ini = meio + EPS;
			}
			else fim = meio - EPS;
		}
		printf("%.4lf\n",resp);
	}
	return 0;
}
