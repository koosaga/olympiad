// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1813
#include <cstdio>
#include <queue>
#include <vector>
#define MAXN 101
#define LIMIT 1000000000
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
vector<iii> grafo[MAXN];
int n,m,q,processado[MAXN],distancias[MAXN],tempos[MAXN];
int main(){
	int instancia = 1;
	while(scanf("%d %d",&n,&m) && (n || m)){
		printf("Instancia %d\n",instancia++);
		for(int i=0;i<=n;i++){
			grafo[i].clear();
		}
		while(m--){
			int u,v,peso1,peso2;
			scanf("%d %d %d %d",&u,&v,&peso1,&peso2);
			grafo[u].push_back(MP(v,MP(peso1,peso2)));
		}
		scanf("%d",&q);
		while(q--){
			int origem,destino,maximo_t,possivel = 0;
			scanf("%d %d %d",&origem,&destino,&maximo_t);
			for(int i=1;i <= n;i++){
				processado[i] = 0;
			}
			priority_queue<iii, vector<iii>, greater<iii> > Dijkstra;
			Dijkstra.push(MP(0,MP(0,origem)));
			while(!Dijkstra.empty()){
				iii davez = Dijkstra.top();
				Dijkstra.pop();
				int v = davez.second.second, distv = davez.first, tempov = davez.second.first;
				if (tempov > maximo_t) continue;
				if(processado[v] == 1){
					if (tempov > tempos[v] && distv > distancias[v]) continue;
				}
				else{
					processado[v] = 1;
					distancias[v] = distv;
					tempos[v] = tempov;
				}
				if(v == destino){
					possivel = 1;
					printf("Possivel - %d km, %d min\n",distv,tempov);
					break;
				}
				for(int i=0;i < grafo[v].size(); i++){
					int u = grafo[v][i].first, distu = grafo[v][i].second.first, tempou = grafo[v][i].second.second;
					Dijkstra.push(MP(distv + distu,MP(tempov+tempou,u)));
				}
			}
			if(!possivel) printf("Impossivel\n");
		}
		printf("\n");
	}
	return 0;
}
