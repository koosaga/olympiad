// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1549
#include <cstdio>
#include <cmath>
const double PI = acos(-1.0);
const double EPS = 1e-4;
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		int n,cap;
		double ini,fim,meio,resp,r,R,altura;
		scanf("%d %d",&n,&cap);
		scanf("%lf %lf %lf",&r,&R,&altura);
		ini = 0.0;
		fim  = altura;
		while(fim - ini > EPS){
			meio = (ini+fim)*0.5;
			double B = r + ((R - r)/altura)*meio;
			double volume = PI*meio*(B*B + B*r + r*r) / 3.0;
			if(n*volume >= cap){
				resp = meio;
				fim = meio - EPS;
			}
			else ini = meio + EPS;
		}
		printf("%.2lf\n",resp);
	}
	return 0;
}
