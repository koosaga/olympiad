// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1205
#include <cstdio>
#include <queue>
#include <vector>
#include <cmath>
#define MAXN 1001
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<int> grafo[MAXN];
int processado[MAXN],soldados[MAXN],n,m,k,a,ini,fim,possivel;
double probabilidade;
int main(){
	while(scanf("%d %d %d %lf",&n,&m,&k,&probabilidade) != EOF){
		possivel = 0;
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			processado[i] = 0;
			soldados[i] = 0;
		}
		while(m--){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		priority_queue<ii> Dijkstra;
		scanf("%d",&a);
		while(a--){
			int davez;
			scanf("%d",&davez);
			soldados[davez]++;
		}
		scanf("%d %d",&ini,&fim);
		Dijkstra.push(MP(k - soldados[ini],ini));
		while(!Dijkstra.empty()){
			ii davez = Dijkstra.top();
			Dijkstra.pop();
			int balas = davez.first, atual = davez.second;
			if(balas < 0) continue;
			if(atual == fim){
				possivel = 1;
				printf("%.3lf\n",pow(probabilidade,k - balas));
				break;
			}
			if(processado[atual]) continue;
			processado[atual] = 1;
			for(int i=0;i<grafo[atual].size();i++){
				int proximo = grafo[atual][i];
				Dijkstra.push(MP(balas - soldados[proximo],proximo));
			}
		}
		if(!possivel) printf("0.000\n");
	}
	return 0;
}
