// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc18c4p5
#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> trinca;

const int MAXN = 2*1e5 + 10;

vector<trinca> grafo[MAXN];
int N,K,especial[MAXN];
int somatorio[MAXN],melhor[MAXN][2],resposta;

void add(int v,int u,int w,int t){

	if(t == 0){
		int cand = somatorio[u] + melhor[u][0] + w;
		if(cand > melhor[v][0]){
			melhor[v][1] = melhor[v][0];
			melhor[v][0] = cand;
		}
		else if(cand > melhor[v][1]){
			melhor[v][1] = cand;
		}
	}
	else{
		int cand = melhor[u][0] - w;
		if(cand > melhor[v][0]){
			melhor[v][1] = melhor[v][0];
			melhor[v][0] = cand;
		}
		else if(cand > melhor[v][1]){
			melhor[v][1] = cand;
		}
		somatorio[v] += 2*w + somatorio[u];
	}

}

void dfs1(int v,int p){

	for(trinca e : grafo[v]){
		int u = get<0>(e), w = get<1>(e), t = get<2>(e);
		if(u == p) continue;
		dfs1(u,v);
		add(v,u,w,t);
	}

}

void dfs2(int v,int p){

	resposta = max(resposta, somatorio[v] + melhor[v][0] );

	for(trinca e : grafo[v]){

		// Vertice e copia
		int u = get<0>(e), w = get<1>(e), t = get<2>(e);
		if(u == p) continue;
		int copia_melhor0 = melhor[v][0],copia_melhor1 = 
melhor[v][1],copia_somatorio = somatorio[v];

		// Removendo u de v
		if(t == 0){
			int cand = somatorio[u] + melhor[u][0] + w;
			if(cand == melhor[v][0]) melhor[v][0] = 
melhor[v][1]; // removemos u da resposta
		}
		else{
			int cand = melhor[u][0] - w;
			if(cand == melhor[v][0]) melhor[v][0] = 
melhor[v][1]; // removemos u da resposta
			somatorio[v] -= somatorio[u] + 2*w; // removemos 
u d resposta
		}

		// Adicionando v a u e chamando o dfs
		add(u,v,w,t);
		dfs2(u,v);

		// Restaurando
		melhor[v][0] = copia_melhor0;
		melhor[v][1] = copia_melhor1;
		somatorio[v] = copia_somatorio;

	}

}

int main(){

	scanf("%d %d",&N,&K);
	for(int i = 1;i<=K;i++){
		int a;
		scanf("%d",&a);
		especial[a] = 1;
	}

	for(int i = 1;i<N;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		grafo[v].push_back(make_tuple(u,w,especial[i]));
		grafo[u].push_back(make_tuple(v,w,especial[i]));
	}

	dfs1(1,-1);
	dfs2(1,-1);
	printf("%d\n",resposta);

	return 0;

}
