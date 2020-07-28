// Ivan Carvalho
// Solution to https://dmoj.ca/problem/joi14p1
#include "factories.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int MAXN = 5*1e5 + 10;
const ll INF = 1e18;
vector<ii> grafo[MAXN];
vector<int> ctree[MAXN];
ll dist[MAXN][25];
int pai[MAXN],block[MAXN],sz[MAXN],tam,iteracao,versao[MAXN],ptr[MAXN];
ll minimo[MAXN];
int dfs1(int v,int p){
	sz[v] = 1;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		if(u == p || block[u]) continue;
		sz[v] += dfs1(u,v);
	}
	return sz[v];
}
void dfs2(int v,int p,ii &resp){
	int mx = tam - sz[v];
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		if(u == p || block[u]) continue;
		dfs2(u,v,resp);
		mx = max(mx,sz[u]);
	}
	ii davez = ii(mx,v);
	resp = min(resp, davez );
}
void dfs3(int v,int p,ll depth){
	dist[v][ptr[v]++] = depth;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		ll w = (ll)grafo[v][i].second;
		if(u == p || block[u]) continue;
		dfs3(u,v,depth + w);
	}
}
int find_centroid(int v){
	tam = dfs1(v,-1);
	ii resp = ii(tam+1,tam+1);
	dfs2(v,-1,resp);
	v = resp.second;
	dfs3(v,-1,0);
	return v;
}
int decompoe(int v){
	v = find_centroid(v);
	block[v] = 1;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		if(block[u]) continue;
		u = decompoe(u);
		ctree[u].push_back(v);
		ctree[v].push_back(u);
	}
	return v;
}
void dfs4(int v,int p){
	pai[v] = p;
	for(int u : ctree[v]){
		if(u == p) continue;
		dfs4(u,v);
	}
}
void insere(int v){
	int x = v;
	for(int nivel = ptr[x] - 1;nivel>=0;nivel--){
		if(versao[v] != iteracao){
			versao[v] = iteracao;
			minimo[v] = dist[x][nivel];
		}
		else{
			minimo[v] = min(minimo[v], dist[x][nivel] );
		}
		v = pai[v];
	}
}
ll queryup(int v){
	ll resp = INF;
	int x = v;
	for(int nivel = ptr[x] - 1;nivel>=0;nivel--){
		if(versao[v] == iteracao) resp = min(resp, minimo[v] + dist[x][nivel] );
		v = pai[v];
	}
	return resp;
}
void Init(int N, int A[], int B[], int D[]){
	for(int i = 0;i<=N-2;i++){
		grafo[A[i]].push_back(ii(B[i],D[i]));
		grafo[B[i]].push_back(ii(A[i],D[i]));
	}
	int raiz = decompoe(0);
	dfs4(raiz,-1);
}
long long Query(int S, int X[], int T, int Y[]){
	ll resp = INF;
	iteracao++;
	for(int i = 0;i<=S-1;i++){
		insere(X[i]);
	}
	for(int i = 0;i<=T-1;i++){
		resp = min(resp, queryup(Y[i]) );
	}
	return resp;
}
int main(){return 0;}
	}
	return resp;
}
int main(){return 0;}