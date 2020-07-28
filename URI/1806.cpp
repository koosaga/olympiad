// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1806
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#define LIMIT 100000
#define MAXN 10100
#define MP make_pair
#define PB push_back
using namespace std;
typedef pair<int,int> ii;
typedef vector<ii> vii;
vii grafo_bino[MAXN],grafo_criminosos[MAXN];
int distancias_bino[MAXN],distancias_criminosos[MAXN],bandidos[MAXN],resposta,visitado_bino[MAXN],visitado_criminosos[MAXN];
int main(){
	int n , c, s, b,tempobino,k,f;
	scanf("%d %d %d %d",&n,&c,&s,&b);
	for(int i=0;i<n;i++) {
		distancias_bino[i] = LIMIT;
		distancias_criminosos[i] = LIMIT;
	}
	for(int i=0;i<c;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		grafo_bino[u-1].PB(MP(v-1,peso));
		grafo_bino[v-1].PB(MP(u-1,peso));
		grafo_criminosos[u-1].PB(MP(v-1,peso));
		grafo_criminosos[v-1].PB(MP(u-1,peso));
	}
	for(int i=0;i<s;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		grafo_criminosos[u-1].PB(MP(v-1,peso));
		grafo_criminosos[v-1].PB(MP(u-1,peso));
	}
	for(int i=0;i<b;i++) scanf("%d",&bandidos[i]);
	scanf("%d %d",&k,&f);
	priority_queue<ii,vii, greater<ii> > fila_bino,fila_criminosos;
	fila_bino.push(MP(0,f-1));
	while(!fila_bino.empty()){
		ii davez = fila_bino.top();
		fila_bino.pop();
		if (visitado_bino[davez.second]) continue;
		visitado_bino[davez.second] = 1;
		distancias_bino[davez.second] = min(distancias_bino[davez.second],davez.first);
		for (vii::iterator it = grafo_bino[davez.second].begin();it!=grafo_bino[davez.second].end();it++){
			ii atual = *it;
			if (!visitado_bino[atual.first]) fila_bino.push(MP(atual.second+davez.first,atual.first));
		}
	}
	fila_criminosos.push(MP(0,f-1));
	while(!fila_criminosos.empty()){
		ii davez = fila_criminosos.top();
		fila_criminosos.pop();
		if (visitado_criminosos[davez.second]) continue;
		visitado_criminosos[davez.second] = 1;
		distancias_criminosos[davez.second] = min(distancias_criminosos[davez.second],davez.first);
		for (vii::iterator it = grafo_criminosos[davez.second].begin();it!=grafo_criminosos[davez.second].end();it++){
			ii atual = *it;
			if (!visitado_criminosos[atual.first]) fila_criminosos.push(MP(atual.second+davez.first,atual.first));
		}
	}
	tempobino = distancias_bino[k-1];
	for(int i=0;i<b;i++) if (distancias_criminosos[bandidos[i]-1]<=tempobino) resposta++;
	printf("%d\n",resposta);
	return 0;
}
