// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1423
#include <cstdio>
#include <algorithm>
#include <queue>
#define MAXN 101
#define MAXK 11
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef pair<int,iii> iiii;
const int INF = 1e7;
vector<ii> grafo[MAXN];
int processado[MAXN][MAXK],a,b,m,l,k;
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d %d %d %d %d",&a,&b,&m,&l,&k);
		for(int i=1;i<=a+b;i++){
			grafo[i].clear();
			for(int j=0;j<=k;j++){
				processado[i][j] = -1;
			}
		}
		while(m--){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			grafo[u].push_back(MP(v,peso));
			grafo[v].push_back(MP(u,peso));
		}
		priority_queue<iiii, vector<iiii> , greater<iiii> > Dijkstra;
		Dijkstra.push(MP(0,MP(k,MP(0,a+b))));
		while(!Dijkstra.empty()){
			iiii davez = Dijkstra.top();
			Dijkstra.pop();
			int percorrido = davez.first, restam = davez.second.first, ainda = davez.second.second.first, v = davez.second.second.second;
			if(v >= a+1) ainda = 0;
			//printf("Percorrido %d Restam %d Ainda %d V %d\n",percorrido,restam,ainda,v);
			if(v == 1){
				printf("%d\n",percorrido);
				break;
			}
			if(processado[v][restam] >= ainda) continue;
			processado[v][restam] = ainda;
			for(int i=0;i<grafo[v].size();i++){
				int u = grafo[v][i].first, peso = grafo[v][i].second;
				if(peso <= ainda) Dijkstra.push(MP(percorrido,MP(restam,MP(ainda - peso,u))));
				if(peso <= l && restam >= 1) Dijkstra.push(MP(percorrido,MP(restam-1,MP(l - peso,u))));
				Dijkstra.push(MP(percorrido+peso,MP(restam,MP(0,u))));
			}
		}
	}
	return 0;
}
