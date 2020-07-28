// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c7p5
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 3*1e5 + 10;
const double EPS = 1e-7;
int vetor[MAXN],n,k;
double a[MAXN],minimo[MAXN];
int func(double val){
	for(int i=1;i<=n;i++) a[i] = vetor[i] - val;
	double tot = 0;
	for(int i=1;i<=k;i++) tot += a[i];
	if(tot + EPS >= 0) return 1;
	double minimo = a[1];
	double ac = 0;
	for(int i = k + 1;i<=n;i++){
		ac += a[i-k];
		minimo = min(ac,minimo);
		tot += a[i];
		if(tot - minimo + EPS >= 0) return 1;
	} 
	return 0;
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&vetor[i]);
	double ini = 1.0,fim = 1e6,meio;
	while(fim - ini > EPS){
		meio = (ini + fim)*0.5;
		if(func(meio)){
			ini = meio + EPS;
		}
		else{
			fim = meio - EPS;
		}
	}
	printf("%.6lf\n",ini);
	return 0;
}