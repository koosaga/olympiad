// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1442
// Ivan Carvalho
// Desvio de Rua - Maratona de Programação 2011
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 1001
using namespace std;
vector<int> grafo[MAXN],transposto[MAXN],bidirecional[MAXN],tipo[MAXN];
int processado[MAXN],n,m,pai[MAXN],conjuntos,iteracao,hapontes;
int dfs_low[MAXN],dfs_num[MAXN],dfs_parent[MAXN],pontosdearticulacao[MAXN],dfsNumberCounter,dfsRoot,dfsRootChildren;
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);y=find(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	pai[y] = x;
	conjuntos--;
}
int dfs1(int x){
	processado[x] = iteracao;
	int retorna = 1;
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(processado[v] != iteracao) retorna += dfs1(v);
	}
	//printf("Dfs1(%d) = %d\n",x,retorna);
	return retorna;
}
int dfs2(int x){
	processado[x] = iteracao;
	int retorna = 1;
	for(int i=0;i<transposto[x].size();i++){
		int v = transposto[x][i];
		if(processado[v] != iteracao) retorna += dfs2(v);
	}
	//printf("Dfs2(%d) = %d\n",x,retorna);
	return retorna;
}
int fortemente_conexo(){
	iteracao++;
	int res1 = dfs1(1);
	//printf("\n");
	if(res1 != n) return 0;
	iteracao++;
	int res2 = dfs2(1);
	//printf("\n");
	if(res2 != n) return 0;
	return 1;
}
void dfs(int u){
	dfs_low[u] = dfs_num[u] = ++dfsNumberCounter;
	for(int i=0;i<bidirecional[u].size();i++){
		int v = bidirecional[u][i];
		if(dfs_num[v] == 0){
			dfs_parent[v] = u;
			if(u == dfsRoot) dfsRootChildren++;
			dfs(v);
			if(dfs_low[v] >= dfs_num[u]){
				pontosdearticulacao[u] = 1;
			}
			if(dfs_low[v] > dfs_num[u]){
				//printf("%d %d is bridge\n",u,v);
				//printf("%d %d\n",v,u);
				if(tipo[u][i] == 1) hapontes = 1;
			}
			dfs_low[u] = min(dfs_low[v],dfs_low[u]);
		}
		else if(v != dfs_parent[u]){
			dfs_low[u] = min(dfs_num[v],dfs_low[u]);
		}
	}
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		conjuntos = n;
		iteracao = 0;
		hapontes = 0;
		dfsNumberCounter = 0;
		for(int i=1;i<=n;i++){
			pai[i] = i;
			processado[i] = 0;
			grafo[i].clear();
			transposto[i].clear();
			bidirecional[i].clear();
			tipo[i].clear();
			dfs_low[i] = dfs_num[i] = dfs_parent[i] = pontosdearticulacao[i] = 0;
		}
		int u,v,ntipo;
		scanf("%d %d %d",&u,&v,&ntipo);
		for(int i=1;i<m;i++){
			scanf("%d %d %d",&u,&v,&ntipo);
			join(u,v);
			if(ntipo == 1){
				grafo[u].push_back(v);
				transposto[v].push_back(u);
			}
			else{
				grafo[u].push_back(v);
				transposto[u].push_back(v);
				grafo[v].push_back(u);
				transposto[v].push_back(u);
			}
			bidirecional[u].push_back(v);
			bidirecional[v].push_back(u);
			tipo[u].push_back(ntipo);
			tipo[v].push_back(ntipo);
		}
		if(conjuntos != 1){
			printf("*\n");
			continue;
		}
		if(fortemente_conexo()){
			printf("-\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(dfs_num[i] == 0){
				dfsRoot = i;
				dfsRootChildren = 0;
				dfs(i);
				pontosdearticulacao[i] = (dfsRootChildren > 1);
			}
		}
		if(hapontes) printf("2\n");
		else printf("1\n");
	}
	return 0;
}
