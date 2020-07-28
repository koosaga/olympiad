// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1123
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define MP make_pair
#define PB push_back
#define MAXN 260
#define LIMIT 9999999
using namespace std;
typedef pair<int,int> ii;
int visitado[MAXN];
vector<ii> grafo[MAXN];
int main(){
	int n,m,c,k;
	while(scanf("%d %d %d %d",&n,&m,&c,&k) && (n||m||c||k)){
		for(int i=0;i<=n;i++) grafo[i].clear(),visitado[i]=0;
		while(m--){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			grafo[u].PB(MP(v,peso));
			grafo[v].PB(MP(u,peso));
		}
		priority_queue<ii, vector<ii>, greater<ii> > dijkstra;
		dijkstra.push(MP(0,k));
		while(!dijkstra.empty()){
			ii davez = dijkstra.top();
			dijkstra.pop();
			if (visitado[davez.second]) continue;
			visitado[davez.second] = 1;
			if (davez.second == c-1){
				printf("%d\n",davez.first);
				break;
			}
			if (davez.second <= c-1){
				for(int i=0;i<grafo[davez.second].size();i++){
					if (grafo[davez.second][i].first==davez.second+1){
						dijkstra.push(MP(grafo[davez.second][i].second+davez.first,davez.second+1));
						break;
					}
				}
			}
			else{
				for(int i=0;i<grafo[davez.second].size();i++) dijkstra.push(MP(grafo[davez.second][i].second+davez.first,grafo[davez.second][i].first));
			}
		}
	}
	return 0;
}
