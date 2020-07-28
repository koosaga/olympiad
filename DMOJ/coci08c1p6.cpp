// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c1p6
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 3*1e5 + 10;
vector<int> grafo[MAXN];
set<ii> cjt[MAXN],maioral[MAXN];
int ecentricidade[MAXN],diametro[MAXN];
int melhor,n,escolhido1,escolhido2,best,aux;
inline int teto(int x){
	return (x+1)/2;
}
int utilidade(int v){
	if(cjt[v].empty()){
		ecentricidade[v] = diametro[v] = 0;
	}
	else if(cjt[v].size() == 1){
		int maior_e = (*cjt[v].rbegin()).first;
		int maior_d = (*maioral[v].rbegin()).first;
		ecentricidade[v] = maior_e + 1;
		diametro[v] = max(maior_d, ecentricidade[v] );
	}
	else{
		int maior_e = (*cjt[v].rbegin()).first;
		int segundo_e = (*next(cjt[v].rbegin())).first;
		int maior_d = (*maioral[v].rbegin()).first;
		diametro[v] = max(maior_d, maior_e +segundo_e + 2 );
		ecentricidade[v] = maior_e + 1;
	}
}
void dfs1(int v,int p){
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs1(u,v);
		maioral[v].insert(ii(diametro[u],u));
		cjt[v].insert(ii(ecentricidade[u],u));
	}
	utilidade(v);
}
void dfs2(int v,int p){
	for(int u : grafo[v]){
		if(u == p) continue;
		ii antigo1 = ii(diametro[u],u), antigo2 = ii(ecentricidade[u],u);
		maioral[v].erase(antigo1);
		cjt[v].erase(antigo2);
		utilidade(v);
		int novo = max(max(diametro[v],diametro[u]),teto(diametro[v]) + teto(diametro[u]) + 1);
		if(novo < melhor){
			melhor = novo;
			escolhido1 = u;
			escolhido2 = v;
		}
		maioral[u].insert(ii(diametro[v],v));
		cjt[u].insert(ii(ecentricidade[v],v));
		dfs2(u,v);
		maioral[v].insert(antigo1);
		cjt[v].insert(antigo2);
	}
}
void dfs3(int v,int p,int depth){
	ecentricidade[v] = max(ecentricidade[v],depth);
	if(depth > best){
		best = depth;
		aux = v;
	}
	for(int u : grafo[v]){
		if(u == p || (u == escolhido1 && v == escolhido2) || (u == escolhido2 && v == escolhido1)) continue;
		dfs3(u,v,depth+1);
	}
}
void dfs4(int v,int p, ii &resp){
	resp = min(resp, ii(ecentricidade[v],v) );
	for(int u : grafo[v]){
		if(u == p || (u == escolhido1 && v == escolhido2) || (u == escolhido2 && v == escolhido1)) continue;
		dfs4(u,v,resp);
	}
}
int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	cin >> n;
	for(int i=1;i<n;i++){
		int u,v;
		cin >> u >>v;
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	melhor= 2*n;
	dfs1(1,-1);
	dfs2(1,-1);
	memset(ecentricidade,0,sizeof(ecentricidade));
	best = 0, aux = 0;
	dfs3(escolhido1,0,0);
	best = 0;
	dfs3(aux,0,0);
	int diametro1 = best;
	dfs3(aux,0,0);
	ii par1 = ii(MAXN,MAXN);
	dfs4(escolhido1,0,par1);
	best = 0, aux = 0;
	dfs3(escolhido2,0,0);
	best = 0;
	dfs3(aux,0,0);
	int diametro2 = best;
	dfs3(aux,0,0);
	ii par2 = ii(MAXN,MAXN);
	dfs4(escolhido2,0,par2);
	cout << melhor << endl;
	cout << escolhido1 << " " << escolhido2 << endl;
	cout << par1.second << " " << par2.second << endl;
	return 0;
}" " << par2.second << endl;
	return 0;
}