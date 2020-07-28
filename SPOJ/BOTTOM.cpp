// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BOTTOM/
#include <cstdio>
#include <vector>
#include <stack>
#define MAXN 5001
using namespace std;
stack<int> pilha;
vector<int> grafo[MAXN],transposto[MAXN],arestas1,arestas2;
int processado1[MAXN],processado2[MAXN],n,m,ID,componente[MAXN],grau[MAXN];
void dfs1(int x){
	processado1[x] = 1;
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(!processado1[v]) dfs1(v);
	}
	pilha.push(x);
}
void dfs2(int x){
	processado2[x] = 1;
	componente[x] = ID;
	for(int i=0;i<transposto[x].size();i++){
		int v = transposto[x][i];
		if(!processado2[v]) dfs2(v);
	}
}
int main(){
	while(scanf("%d",&n) && n){
		scanf("%d",&m);
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			transposto[i].clear();
			componente[i] = 0;
			grau[i] = 0;
			processado1[i] = 0;
			processado2[i] = 0;
		}
		arestas1.clear();
		arestas2.clear();
		ID = 0;
		while(!pilha.empty()) pilha.pop();
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			transposto[v].push_back(u);
			arestas1.push_back(u);
			arestas2.push_back(v);
		}
		for(int i=1;i<=n;i++){
			if(!processado1[i]) dfs1(i);
		}
		while(!pilha.empty()){
			int i = pilha.top();
			pilha.pop();
			if(!processado2[i]){
				ID++;
				dfs2(i);
			}
		}
		for(int i=0;i<m;i++){
			if(componente[arestas1[i]] != componente[arestas2[i]]){
				grau[componente[arestas1[i]]]++;
			}
		}
		int primeiro = 0;
		for(int i=1;i<=n;i++){
			if(grau[componente[i]] != 0) continue;
			if(primeiro) printf(" ");
			else primeiro = 1;
			printf("%d",i);
		}
		printf("\n");
	}
	return 0;
}