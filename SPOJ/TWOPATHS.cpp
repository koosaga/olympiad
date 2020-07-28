// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TWOPATHS/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
vector<int> grafo[MAXN];
int maior_dist[MAXN][3],maior_diam[MAXN][2];
int temporario_diametro[MAXN],temporario_dist[MAXN],N;
ll melhor_produto;
void calcula(int v){
	temporario_dist[v] = maior_dist[v][0];
	temporario_diametro[v] = max(maior_diam[v][0],maior_dist[v][0] + maior_dist[v][1]);
}
void insert(int v,int u){
	int ndist = temporario_dist[u] + 1;
	if(ndist > maior_dist[v][0]){
		maior_dist[v][2] = maior_dist[v][1];
		maior_dist[v][1] = maior_dist[v][0];
		maior_dist[v][0] = ndist;
	}
	else if(ndist > maior_dist[v][1]){
		maior_dist[v][2] = maior_dist[v][1];
		maior_dist[v][1] = ndist;
	}
	else if(ndist > maior_dist[v][2]){
		maior_dist[v][2] = ndist;
	}
	int ndiam = temporario_diametro[u];
	if(ndiam > maior_diam[v][0]){
		maior_diam[v][1] = maior_diam[v][0];
		maior_diam[v][0] = ndiam;
	}
	else if(ndiam > maior_diam[v][1]){
		maior_diam[v][1] = ndiam;
	}
	calcula(v);
}
void remove(int v,int u){
	int ndist = temporario_dist[u] + 1;
	int ndiam = temporario_diametro[u];
	if(ndist == maior_dist[v][0]){
		maior_dist[v][0] = maior_dist[v][1];
		maior_dist[v][1] = maior_dist[v][2];
	}
	else if(ndist == maior_dist[v][1]){
		maior_dist[v][1] = maior_dist[v][2];
	}
	if(ndiam == maior_diam[v][0]){
		maior_diam[v][0] = maior_diam[v][1];
	}
	calcula(v);
}
void dfs1(int v,int p){
	calcula(v);
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs1(u,v);
		insert(v,u);
	}
}
void dfs2(int v,int p){
	calcula(v);
	for(int u : grafo[v]){
		if(u == p) continue;
		int copiav_dist[3],copiav_diam[2],copiau_dist[3],copiau_diam[2];
		copiav_dist[0] = maior_dist[v][0];copiav_dist[1] = maior_dist[v][1];copiav_dist[2] = maior_dist[v][2];
		copiau_dist[0] = maior_dist[u][0];copiau_dist[1] = maior_dist[u][1];copiau_dist[2] = maior_dist[u][2];
		copiav_diam[0] = maior_diam[v][0];copiav_diam[1] = maior_diam[v][1];
		copiau_diam[0] = maior_diam[u][0];copiau_diam[1] = maior_diam[u][1];
		remove(v,u);
		ll candidato = 1LL*temporario_diametro[v]*temporario_diametro[u];
		melhor_produto = max(melhor_produto,candidato);
		insert(u,v);
		dfs2(u,v);
		maior_dist[v][0] = copiav_dist[0];maior_dist[v][1] = copiav_dist[1];maior_dist[v][2] = copiav_dist[2];
		maior_dist[u][0] = copiau_dist[0];maior_dist[u][1] = copiau_dist[1];maior_dist[u][2] = copiau_dist[2];
		maior_diam[v][0] = copiav_diam[0];maior_diam[v][1] = copiav_diam[1];
		maior_diam[u][0] = copiau_diam[0];maior_diam[u][1] = copiau_diam[1];
		calcula(v);
		calcula(u);
	}
}
int main(){
	scanf("%d",&N);
	for(int i = 1;i<N;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	dfs1(1,-1);
	//printf("MaiorDiam 1 %d\n",temporario_diametro[1]);
	dfs2(1,-1);
	printf("%lld\n",melhor_produto);
	return 0;
}