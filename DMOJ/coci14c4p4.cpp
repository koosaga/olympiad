// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c4p4
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
const int MAXN = 1010;
const double EPS = 1e-5;
double requer[MAXN];
vector<int> grafo[MAXN],tipo[MAXN];
vector<double> porcentagem[MAXN];
int n;
int dfs(int v,int p,double recebe){
	int ret = recebe + EPS >= requer[v];
	for(int i=0;i<grafo[v].size();i++){
		int u = grafo[v][i];
		if(u == p) continue;
		double cof = porcentagem[v][i];
		int quadrado = tipo[v][i];
		if(quadrado) ret &= dfs(u,v,(cof * recebe)*(cof * recebe));
		else ret &= dfs(u,v,cof*recebe);
	}
	return ret;
}
double bs(){
	double ini = EPS,fim = 2*1e9,meio;
	while(fim - ini > EPS){
		meio = (ini+fim)*0.5;
		if(dfs(1,-1,meio)) fim = meio - EPS;
		else ini = meio + EPS;
	}
	return ini;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v,cof,quadrado;
		scanf("%d %d %d %d",&u,&v,&cof,&quadrado);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
		porcentagem[u].push_back(cof*0.01);
		porcentagem[v].push_back(cof*0.01);
		tipo[u].push_back(quadrado);
		tipo[v].push_back(quadrado);
	}
	for(int i=1;i<=n;i++) scanf("%lf",&requer[i]);
	printf("%.3lf\n",bs());
	return 0;
}