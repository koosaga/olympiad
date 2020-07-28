// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2011
#include <cstdio>
#include <queue>
using namespace std;
const int MAXN = 1e3 + 1;
const int MAXM = 1e2 + 1;
const double INF = 1e18;
const double EPS = 1e-12;
int grafo[MAXN][MAXM],grau[MAXN],n,m,nafila[MAXN];
double A[MAXN][MAXM],B[MAXN][MAXM],dist[MAXN];
double SPFA(double time){
	for(int i=1;i<=n;i++){
		dist[i] = INF;
		nafila[i] = 0;
	}
	dist[1] = 0;
	nafila[1] = 1;
	queue<int> fila;
	fila.push(1);
	while(!fila.empty()){
		int davez = fila.front();
		fila.pop();
		nafila[davez] = 0;
		for(int i=0;i<grau[davez];i++){
			double custo = A[davez][i]*time + B[davez][i];
			int proximo = grafo[davez][i];
			if(dist[davez] + custo < dist[proximo]){
				dist[proximo] = dist[davez] + custo;
				if(!nafila[proximo]){
					nafila[proximo] = 1;
					fila.push(proximo);
				}
			}
		}
	}
	return dist[n];
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		for(int i=1;i<=n;i++){
			grau[i] = 0;
		}
		for(int i=1;i<=m;i++){
			int u,v;
			double ai,bi;
			scanf("%d %d %lf %lf",&u,&v,&ai,&bi);
			grafo[u][grau[u]] = v;
			A[u][grau[u]] = ai;
			B[u][grau[u]++] = bi;
			grafo[v][grau[v]] = u;
			A[v][grau[v]] = ai;
			B[v][grau[v]++] = bi;

		}
		double ini = 0.0, fim = 1440.0, meio1,meio2;
		while(fim - ini > EPS){
			meio1 = ini + (fim - ini)/3.0;
			meio2 = fim - (fim - ini)/3.0;
			if(SPFA(meio1) - EPS < SPFA(meio2)){
				ini = meio1 + EPS;
			}
			else{
				fim = meio2 - EPS;
			}
		}
		printf("%.5lf\n",SPFA(ini));
	}
	return 0;
}
