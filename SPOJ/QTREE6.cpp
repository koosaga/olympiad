// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QTREE6/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
const int BLOCK_SIZE = 400;
vector<ii> Arestas;
vector<int> grafo[MAXN],especiais,processado;
int e1[MAXN],e2[MAXN];
int cor[MAXN],qtd[MAXN][2],marcado[MAXN],pai[MAXN],peso[MAXN],folha[MAXN],n,m;
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(peso[x] < peso[y]) pai[x] = y;
	else if(peso[x] > peso[y]) pai[y] = x;
	else pai[x] = y, peso[y]++;
}
void build_graph(){
	for(int i=1;i<=n;i++){
		pai[i] = i;
		peso[i] = 0;
		qtd[i][0] = qtd[i][1] = 0;
		grafo[i].clear();
		folha[i] = 0;
	}	
	for(int i=0;i<Arestas.size();i++){
		int u = Arestas[i].first;
		int v = Arestas[i].second;
		if(marcado[u] || marcado[v]) continue;
		if(cor[u] == cor[v]) join(u,v);
	}
	for(int i=0;i<Arestas.size();i++){
		int u = find(Arestas[i].first);
		int v = find(Arestas[i].second);
		if(u == v) continue;
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(marcado[i]) continue;
		qtd[find(i)][cor[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(i != find(i)) continue;
		folha[i] = !marcado[i] && (grafo[i].size() == 1);
		if(folha[i]){
			int j = grafo[i][0];
			qtd[j][cor[i]] += qtd[i][cor[i]];
		}
	}
	for(int i=1;i<=n;i++) grafo[i].clear();
	for(int i=0;i<Arestas.size();i++){
		int u = find(Arestas[i].first);
		int v = find(Arestas[i].second);
		if(u == v) continue;
		if(!folha[v]) grafo[u].push_back(v);
		if(!folha[u]) grafo[v].push_back(u);
	}
}
void dfs(int v,int p){
	processado.push_back(v);
	for(int u : grafo[v]){
		if(u == p || cor[u] != cor[v]) continue;
		dfs(u,v);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		Arestas.push_back(MP(u,v));
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		scanf("%d %d",&e1[i],&e2[i]);
	}
	int ini = 0, fim = BLOCK_SIZE - 1;
	while(ini < m){
		fim = min(fim,m-1);
		for(int i : especiais){
			marcado[i] = 0;
		}
		especiais.clear();
		for(int i = ini;i<=fim;i++) if(e1[i] == 1 && !marcado[e2[i]]){
			especiais.push_back(e2[i]);
			marcado[e2[i]] = 1;
		}
		build_graph();
		for(int i = ini;i<=fim;i++){
			int op = e1[i];
			int v = e2[i];
			if(op == 1){
				cor[v] = 1 - cor[v];
				continue;
			}
			processado.clear();
			v = find(v);
			int resp = 0;
			dfs(v,-1);
			for(int u : processado){
				if(folha[u]) continue;
				resp += qtd[u][cor[v]];
				if(marcado[u]) resp++;
			}
			resp = max(resp,qtd[v][cor[v]]);
			printf("%d\n",resp);
		}
		ini += BLOCK_SIZE;
		fim += BLOCK_SIZE;
	}
	return 0;
}