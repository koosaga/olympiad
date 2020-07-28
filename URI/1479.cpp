// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1479
#include <cstdio>
#include <queue>
#include <map>
#define MAXN 1001
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
map<int,int> grafo[MAXN];
int processado[MAXN],n,m,k;
int Dijkstra(int destino){
	for(int i=1;i<=n;i++){
		processado[i] = 0;
	}
	priority_queue<ii, vector<ii>, greater<ii> > fila;
	fila.push(MP(0,1));
	while(!fila.empty()){
		ii davez = fila.top();
		fila.pop();
		int v = davez.second, percorrido = davez.first;
		if(processado[v]) continue;
		processado[v] = 1;
		if(v == destino) return percorrido;
		for(auto it = grafo[v].begin();it != grafo[v].end();it++){
			int u = (*it).first, peso = (*it).second;
			fila.push(MP(percorrido+peso,u));
		}
	}
	return -1;
}
int main(){
	while(scanf("%d %d",&n,&m) && (n||m)){
		for(int i=1;i<=n;i++){
			grafo[i].clear();
		}
		while(m--){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			grafo[u][v] = peso;
		}
		scanf("%d",&k);
		while(k--){
			char op;
			scanf(" %c",&op);
			if(op == 'P'){
				int destino;
				scanf("%d",&destino);
				printf("%d\n",Dijkstra(destino));
			}
			else if(op == 'R'){
				int a,b;
				scanf("%d %d",&a,&b);
				grafo[a].erase(b);
			}
			else if(op == 'I'){
				int a,b,peso;
				scanf("%d %d %d",&a,&b,&peso);
				grafo[a][b] = peso;
			}
		}
		printf("\n");
	}
	return 0;
}
