// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1391
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#define MAXN 501
#define LIMIT 500000010
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int, vector<ii> > sii;
typedef pair<int,sii> isii;
vector<ii> grafo[MAXN];
int proibido[MAXN],processado[MAXN],menordist[MAXN],possivel,matriz[MAXN][MAXN];
int main(){
	int n,m,ini,fim;
	while(scanf("%d %d",&n,&m) && (n || m)){
		scanf("%d %d",&ini,&fim);
		for(int i=0;i<n;i++){
			grafo[i].clear();
			proibido[i] = 0;
			menordist[i] = LIMIT;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				matriz[i][j] = LIMIT;
			}
			matriz[i][i] = 0;
		}
		possivel = 0;
		while(m--){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			grafo[u].push_back(MP(v,peso));
			matriz[u][v] = peso;
		}
		vector<ii> vazio;
		priority_queue<isii, vector<isii>, greater<isii> > Dijkstra;
		Dijkstra.push(MP(0,MP(ini,vazio)));
		while(!Dijkstra.empty()){
			isii davez = Dijkstra.top();
			Dijkstra.pop();
			int percorrido = davez.first, v = davez.second.first;
			vector<ii> conjunto = davez.second.second;
			if(percorrido > menordist[v]) continue;
			menordist[v] = percorrido;
			if(v == fim){
				for(auto it = conjunto.begin();it != conjunto.end();it++){
					//printf("%d %d nao existe mais\n",(*it).first,(*it).second);
					matriz[(*it).first][(*it).second] = LIMIT;
				}
				continue;
			}
			for(int i=0;i<grafo[v].size();i++){
				int u = grafo[v][i].first, peso = grafo[v][i].second;
				conjunto.push_back(MP(v,u));
				Dijkstra.push(MP(percorrido+peso,MP(u,conjunto)));
				conjunto.pop_back();
			}
		}
		for(int k=0;k<n;k++){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					matriz[i][j] = min(matriz[i][j],matriz[i][k] + matriz[k][j]);
				}
			}
		}
		if(matriz[ini][fim] != LIMIT) printf("%d\n",matriz[ini][fim]);
		else printf("-1\n");
	}
	return 0;
}
