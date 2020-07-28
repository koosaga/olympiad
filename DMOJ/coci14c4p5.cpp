// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c4p5
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2*1e5 + 10;

vector<int> grafo[MAXN];
int cor[MAXN],N;

int calcula_erro(int v){
	int total = 0;
	for(int u : grafo[v]) total += (cor[v] == cor[u]);
	return total;
}

void dfs(int v){
	int erros = calcula_erro(v);
	if(erros <= 2){
		return;
	}
	cor[v] ^= 1;
	for(int u : grafo[v]){
		dfs(u);
	}
}

int main(){

	scanf("%d",&N);
	for(int dia = 1;dia<=5;dia++){
		int pares;
		scanf("%d",&pares);
		while(pares--){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
	}

	for(int i = 1;i<=N;i++){
		sort(grafo[i].begin(),grafo[i].end());
		grafo[i].erase(unique(grafo[i].begin(),grafo[i].end()),grafo[i].end());
	}

	for(int i = 1;i<=N;i++){
		dfs(i);
	}

	for(int i = 1;i<=N;i++){
		if(cor[i] == 0) printf("A");
		else printf("B");
	}
	printf("\n");

	return 0;
}