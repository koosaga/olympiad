// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1413
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define MAXN 211
#define MP make_pair
using namespace std;
const double INF = 1e9;
const double EPS = 1e-9;
typedef pair<double,int> di;
vector<int> grafo[MAXN];
int n,m,V,cap[MAXN][MAXN],anterior[MAXN];
double custo[MAXN][MAXN],velocidade[MAXN],X[MAXN],Y[MAXN],dist[MAXN];
int Dijkstra(){
	//printf("Dijkstra\n");
	for(int i=0;i<=V;i++){
		dist[i] = INF;
		anterior[i] = -1;
	}
	dist[0] = 0;
	anterior[0] = 0;
	priority_queue<di, vector<di>, greater<di> > SSSP;
	SSSP.push(MP(0.0,0));
	while(!SSSP.empty()){
		di davez = SSSP.top();
		SSSP.pop();
		double percorrido = davez.first;
		int v = davez.second;
		//printf("%d\n",v);
		if(dist[v] > percorrido + EPS) continue;
		if(v == V) break;
		for(int u : grafo[v]){
			if(dist[v] + custo[v][u] + EPS <= dist[u] && cap[v][u] > 0){
				dist[u] = dist[v] + custo[v][u];
				anterior[u] = v;
				SSSP.push(MP(dist[u],u));
			}
		}
	}
	if(dist[V] == INF) return 0;
	vector<int> caminho;
	caminho.push_back(V);
	int atual = V;
	while(atual != 0){
		caminho.push_back(anterior[atual]);
		atual = anterior[atual];
	}
	reverse(caminho.begin(),caminho.end());
	int temp = MAXN;
	//printf("%d",caminho[0]);
	for(int i=0;i + 1 < caminho.size();i++){
		//printf(" %d",caminho[i+1]);
		temp = min(temp, cap[caminho[i]][caminho[i+1]] );
	}
	//printf("\n");
	for(int i=0;i+1 < caminho.size();i++){
		cap[caminho[i]][caminho[i+1]] -= temp;
		cap[caminho[i+1]][caminho[i]] += temp;
	}
	return 1;
}
double Edmond(){
	double total = 0.0;
	while(true){
		if(!Dijkstra()) break;
	}
	for(int i = 1;i <= n;i++){
		for(int j : grafo[i]){
			if(cap[i][j] < 1) total += custo[i][j];
		}
	}
	return total;
}
int main(){
	while(scanf("%d %d",&n,&m) && (n||m)){
		for(int i=0;i<=MAXN;i++){
			grafo[i].clear();
		}
		memset(cap,0,sizeof(cap));
		V = n + m + 1;
		for(int i=1;i<=n;i++){
			grafo[i].push_back(0);
			grafo[0].push_back(i);
			cap[0][i] = 1;
			custo[i][0] = custo[0][i] = 0.0;
		}
		for(int i = n + 1;i <= n+m;i++){
			grafo[i].push_back(V);
			grafo[V].push_back(i);
			cap[i][V] = 1;
			custo[i][V] = custo[V][i] = 0.0;
		}
		for(int i=1;i<=n;i++){
			scanf("%lf %lf %lf",&X[i],&Y[i],&velocidade[i]);
		}
		for(int i= n + 1;i <= n+m;i++){
			scanf("%lf %lf",&X[i],&Y[i]);
			int davez;
			while(scanf("%d",&davez) && davez){
				grafo[i].push_back(davez);
				grafo[davez].push_back(i);
				custo[davez][i] = hypot(X[i] - X[davez],Y[i] - Y[davez]) / velocidade[davez];
				custo[i][davez] = -custo[davez][i];
				cap[davez][i] = 1;
			}
		}
		//for(int i=1;i<=V;i++){
		//	printf("%d:",i);
		//	for(int j : grafo[i]){
		//		printf(" %d",j);
		//	}
		//	printf("\n");
		//}
		printf("%.1lf\n",Edmond());
	}
	return 0;
}
