// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc16s3
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 100010;
vector<int> grafo[MAXN];
int marcado[MAXN],valido[MAXN],aux,diametro,primeiro,n,m,novo;
void dfs(int v,int p){
	valido[v] = marcado[v];
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs(u,v);
		valido[v] |= valido[u];
	}
	if(valido[v]) novo++;
}
void find_diametro(int v,int p,int depth){
	if(depth > diametro){
		diametro = depth;
		aux = v;
	}
	for(int u : grafo[v]){
		if(u == p || !valido[u]) continue;
		find_diametro(u,v,depth+1);
	}
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&primeiro);
		marcado[primeiro] = 1;
	}
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	dfs(primeiro,-1);
	find_diametro(primeiro,-1,0);
	find_diametro(aux,-1,0);
	printf("%d\n",2*(novo-1) - diametro);
	return 0;
}