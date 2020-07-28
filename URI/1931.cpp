// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1931
#include <cstdio>
#include <vector>
#include <queue>
#define LIMIT 9999999
#define MAXN 10002
#define PB push_back
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
int processado[MAXN],c,v;
vector< ii > auxiliar[MAXN], grafo[MAXN];
int main(){
	scanf("%d %d",&c,&v);
	if (v==0){
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=c;i++) {
		grafo[i].clear();
		auxiliar[i].clear();
		processado[i] = 0;
	}
	for(int i=0;i<v;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		auxiliar[u].PB(MP(v,peso));
		auxiliar[v].PB(MP(u,peso));
	}
	for(int i=1;i<=c;i++){
		for(int j=0;j<auxiliar[i].size();j++){
			ii par = auxiliar[i][j];
			for(int k=0;k<auxiliar[par.first].size();k++){
				ii subpar = auxiliar[par.first][k];
				if (subpar.first == i) continue;
				grafo[i].PB(MP(subpar.first,par.second+subpar.second));
				grafo[subpar.first].PB(MP(i,par.second+subpar.second));
			}
		}
	}
	priority_queue<ii, vector<ii> , greater<ii> > sssp;
	int sucesso = 0;
	sssp.push(MP(0,1));
	while(!sssp.empty()){
		ii davez = sssp.top();
		sssp.pop();
		int v = davez.second, percorrido = davez.first;
		if (v == c){
			printf("%d\n",percorrido);
			sucesso = 1;
			break;
		}
		if (processado[v]) continue;
		processado[v] = 1;
		for(int i=0;i<grafo[v].size();i++){
			sssp.push(MP(grafo[v][i].second + percorrido,grafo[v][i].first));
		}
	}
	if (!sucesso) printf("-1\n");
	return 0;
}
