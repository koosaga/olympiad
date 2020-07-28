// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MTREE/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 10;
const ll MAXL = 18;
const ll MOD = 1000000007LL;
typedef pair<int,int> ii;
vector<ii> grafo[MAXN];
vector<int> ctree[MAXN],filhos[MAXN];
int profundidade[MAXN],tam,sz[MAXN],block[MAXN],n;
ll pesototal,somatorio[MAXN],dist[MAXN][MAXL];
int dfs1(int x,int p){
	sz[x] = 1;
	for(int i = 0;i<grafo[x].size();i++){
		int u = grafo[x][i].first;
		if(u == p || block[u]) continue;
		sz[x] += dfs1(u,x);
	}
	return sz[x];
}
void dfs2(int x,int p,ii &resp){
	int mx = tam - sz[x];
	for(int i = 0;i<grafo[x].size();i++){
		int u = grafo[x][i].first;
		if(u == p || block[u]) continue;
		dfs2(u,x,resp);
		mx = max(mx,sz[u]);
	}
	if(mx < resp.first) resp = ii(mx,x);
}
void dfs3(int x,int p,ll depth){
	dist[x][++profundidade[x]] = depth;
	for(int i = 0;i<grafo[x].size();i++){
		int u = grafo[x][i].first;ll peso = (ll)grafo[x][i].second;
		if(u == p || block[u]) continue;
		dfs3(u,x, (depth * peso) % MOD );
	}
}
int find_centroid(int raiz){
	tam = dfs1(raiz,-1);
	ii resp = ii(MAXN,MAXN);
	dfs2(raiz,-1,resp);
	raiz = resp.second;
	dfs3(raiz,-1,1);
	return raiz;
}
int decompoe(int raiz){
	raiz = find_centroid(raiz);
	block[raiz] = 1;
	for(int i = 0;i<grafo[raiz].size();i++){
		int prox = grafo[raiz][i].first;
		if(block[prox]) continue;
		prox = decompoe(prox);
		ctree[raiz].push_back(prox);
		ctree[prox].push_back(raiz);
	}
	return raiz;
}
void conta(int x,int p,int depth){
	filhos[x].push_back(x);
	for(int i = 0;i<ctree[x].size();i++){
		int v = ctree[x][i];
		if(v == p) continue;
		conta(v,x,depth+1);
		for(int j = 0;j<filhos[v].size();j++){
			int u = filhos[v][j];
			pesototal = (pesototal + (dist[u][depth]*somatorio[x])) % MOD;
		}	
		for(int j = 0;j<filhos[v].size();j++){
			int u = filhos[v][j];
			filhos[x].push_back(u);
			somatorio[x] = (somatorio[x] + dist[u][depth]);
		}
		somatorio[x] %= MOD;
	}
	pesototal = (pesototal + somatorio[x]) % MOD;
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		profundidade[i] = -1;
	}
	for(int i = 1;i<n;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		grafo[u].push_back(ii(v,w));
		grafo[v].push_back(ii(u,w));
	}
	int raiz = decompoe(1);
	conta(raiz,-1,0);
	printf("%lld\n",pesototal);
	return 0;
} 