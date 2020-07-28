// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1328
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define MAXN 301
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<ii> grafo[MAXN];
int processado[MAXN],zona[MAXN],n,m,k,ini,fim,t,b;
int main(){
	while(scanf("%d %d",&m,&n) && (n||m)){
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			processado[i] = 0;
		}
		for(int i=1;i<=m;i++){
			int qtd;
			scanf("%d",&qtd);
			while(qtd--){
				int u;
				scanf("%d",&u);
				zona[u] = i;
			}
		}
		scanf("%d %d",&t,&b);
		while(t--){
			int qtd;
			vector<int> pares;
			scanf("%d",&qtd);
			for(int i=0;i<qtd;i++){
				int davez;
				scanf("%d",&davez);
				pares.push_back(davez);
			}
			for(int i=0;i<qtd;i++){
				int custo = 0;
				for(int j=i+1;j<qtd;j++){
					if(zona[pares[i]] != zona[pares[j]]) custo += 4;
					grafo[pares[i]].push_back(MP(pares[j],custo));
					grafo[pares[j]].push_back(MP(pares[i],custo));
				}
			}
		}
		while(b--){
			int qtd;
			vector<int> pares;
			scanf("%d",&qtd);
			for(int i=0;i<qtd;i++){
				int davez;
				scanf("%d",&davez);
				pares.push_back(davez);
			}
			for(int i=0;i<qtd;i++){
				int custo = 1;
				for(int j=i+1;j<qtd;j++){
					grafo[pares[i]].push_back(MP(pares[j],custo));
					grafo[pares[j]].push_back(MP(pares[i],custo));
				}
			}
		}
		scanf("%d %d",&ini,&fim);
		priority_queue<ii, vector<ii>, greater<ii> > Dijkstra;
		Dijkstra.push(MP(2,ini));
		while(!Dijkstra.empty()){
			ii davez = Dijkstra.top();
			Dijkstra.pop();
			int v = davez.second, percorrido = davez.first;
			if(v == fim){
				printf("%d\n",percorrido);
				break;
			}
			if(processado[v]) continue;
			processado[v] = 1;
			for(int i=0;i<grafo[v].size();i++){
				int u = grafo[v][i].first, peso = grafo[v][i].second;
				Dijkstra.push(MP(percorrido+peso,u));
			}
		}
	}
	return 0;
}
