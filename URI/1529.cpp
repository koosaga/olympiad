// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1529
#include <cstdio>
#include <queue>
#include <vector>
#define MP make_pair
#define MAXN 11
#define MAXT 51
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
vector<ii> grafo[MAXN];
int processado[MAXN][MAXT],n,m,t,iteracao,possivel,combustivel[MAXN];
int main(){
	while(scanf("%d %d %d",&n,&m,&t) && (n||m||t)){
		possivel = 0;
		iteracao++;
		for(int i=1;i<=n;i++){
			grafo[i].clear();
		}
		for(int i=1;i<=m;i++){
			int u,v,dist;
			scanf("%d %d %d",&u,&v,&dist);
			grafo[u].push_back(MP(v,dist));
			grafo[v].push_back(MP(u,dist));
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&combustivel[i]);
		}
		priority_queue<iii, vector<iii>, greater<iii> > Dijkstra;
		Dijkstra.push(MP(0,MP(t,1)));
		while(!Dijkstra.empty()){
			iii davez = Dijkstra.top();
			Dijkstra.pop();
			int gasto = davez.first, tanque = davez.second.first, cidade = davez.second.second;
			//printf("Cidade %d Gasto %d Tanque %d\n",cidade,gasto,tanque);
			if(cidade == n){
				printf("%d\n",gasto);
				possivel = 1;
				break;
			}
			if(processado[cidade][tanque] == iteracao) continue;
			processado[cidade][tanque] = iteracao;
			for(int i=tanque+1;i <= t;i++){
				int agrega = (i - tanque)*combustivel[cidade];
				Dijkstra.push(MP(gasto+agrega,MP(i,cidade)));
			}
			for(int i=0;i<grafo[cidade].size();i++){
				int proximo = grafo[cidade][i].first, proxdist = grafo[cidade][i].second;
				if(proxdist <= tanque){
					Dijkstra.push(MP(gasto,MP(tanque-proxdist,proximo)));
				} 
			}
		}
		if(!possivel) printf("-1\n");
	}
	return 0;
}
