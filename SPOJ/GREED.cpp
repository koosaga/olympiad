// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GREED/
#include <bits/stdc++.h>
using namespace std;
 
const int MAXL = 1e5 + 10;
const int MAXN = 1010;
const int INF = 1e9;
 
int cap[MAXN][MAXN],custo[MAXN][MAXN],pai[MAXN],dist[MAXN],nafila[MAXN],N,M;
int equivale1[MAXN],equivale2[MAXN];
 
map<int,int> conversao;
set<int> grafo[MAXL];
map<int,int> percurso[MAXL];
 
int SPFA(){
	//printf("SPFA\n");
	for(int i = 0;i<=M;i++){
		pai[i] = -1;
		dist[i] = INF;
		nafila[i] = 0;
	}
	queue<int> fila;
	dist[0] = 0;
	fila.push(0);
	nafila[0] = 1;
	while(!fila.empty()){
		int v = fila.front();
		nafila[v] = 0;
		fila.pop();
		//printf("V %d dist %d\n",v,dist[v]);
		for(int u = 0;u<=M;u++){
			if(cap[v][u] <= 0) continue;
			if(custo[v][u] + dist[v] < dist[u]){
				dist[u] = custo[v][u] + dist[v];
				pai[u] = v;
				if(!nafila[u]){
					nafila[u] = 1;
					fila.push(u);
				}
			}
		}
	}
	if(dist[M] == INF) return 0;
	int atual = M;
	while(pai[atual] != -1){
		cap[pai[atual]][atual] -= 1;
		cap[atual][pai[atual]] += 1;
		atual = pai[atual];
	}
	return dist[M];
}
 
void bfs(int s){
	queue<int> fila;
	vector<int> vis;
	vis.assign(2*conversao.size()+1,0);
	vis[s] = 1;
	percurso[s][s] = 0;
	fila.push(s);
	while(!fila.empty()){
		int v = fila.front();
		fila.pop();
		for(set<int>::iterator it = grafo[v].begin();it != grafo[v].end();it++){
			int u = *it;
			if(!vis[u]){
				vis[u] = 1;
				percurso[s][u] = percurso[s][v] + 1;
				fila.push(u);
			}
		}
	}
}
 
int get_id(int v){
	if(!conversao.count(v)){
		conversao[v] = conversao.size();
		grafo[v].clear();
		percurso[v].clear();
	}
	//printf("V %d conversao %d\n",v,conversao[v]);
	return conversao[v];
}
 
int main(){
	
	int TC;
	scanf("%d",&TC);
	
	for(int tc = 1;tc<=TC;tc++){
		
		scanf("%d",&N);
		memset(cap,0,sizeof(cap));
		memset(custo,0,sizeof(custo));
		conversao.clear();
		M = 2*N + 1;
 
		for(int i = 1;i<=N;i++) equivale1[i] = get_id(i);
 
		for(int i = 1;i<=N;i++){
			scanf("%d",&equivale2[i]);
			equivale2[i] = get_id(equivale2[i]);
		}
 
		int E;
		scanf("%d",&E);
		while(E--){
			int x,y;
			scanf("%d %d",&x,&y);
			x = get_id(x);
			y = get_id(y);
			//printf("X %d Y %d\n",x,y);
			grafo[x].insert(y);
			grafo[y].insert(x);
		}
 
		//printf("Grafo\n");
 
		for(int i = 1;i<=N;i++) bfs(equivale1[i]);
 
		for(int i = 1;i<=N;i++){
			cap[0][i] = 1;
		}
		for(int i = 1;i<=N;i++){
			cap[N+i][M] = 1;
		}
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				if(percurso[equivale1[i]].count(equivale2[j])){
					custo[i][j+N] = percurso[equivale1[i]][equivale2[j]];
					custo[j+N][i] = -custo[i][j+N];
					cap[i][j+N] = 1;
				}
			}
		}
 
		//printf("Construi\n");
 
		int custo = 0;
		for(int i = 1;i<=N;i++) custo += SPFA();
		printf("%d\n",custo);
 
	}
 
	return 0;
} 
