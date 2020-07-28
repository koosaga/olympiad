// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1860
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const double EPS = 1e-3;
const int MAXN = 5*(1e4 + 1);
double X[MAXN],Y[MAXN];
int n;
double ini,fim,meio1,meio2;
double func(double xdavez){
	double maximo = 0;
	for(int i=1;i<=n;i++){
		maximo = max(maximo, hypot(X[i] - xdavez, Y[i]));
	}
	return maximo;
}
int main(){
	scanf("%d %lf",&n,&fim);
	for(int i=1;i<=n;i++){
		scanf("%lf %lf",&X[i],&Y[i]);
	}
	while(fim - ini > EPS){
		meio1 = ini + (fim - ini)/3.0;
		meio2 = fim - (fim - ini)/3.0;
		if(func(meio1) > func(meio2)) ini = meio1 + EPS;
		else fim = meio2 - EPS;
	}
	printf("%.2lf %.2lf\n",ini,func(ini));
	return 0;
}
