// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QTREE5/
#include <bits/stdc++.h>
#define MAXN 100110
#define MAXL 18
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
const ii NULO = MP(MAXN,MAXN);
int num,nivel[MAXN],pai[MAXN],tam[MAXN],marcado[MAXN],cor[MAXN],dist[MAXN][MAXL],profundidade[MAXN];
vector<int> adj[MAXN],ctree[MAXN];
multiset<int> distancias[MAXN];
int dfs1(int v,int p){
	tam[v] = 1;
	for(int i=0;i<adj[v].size();i++){
		int u = adj[v][i];
		if(u != p && !marcado[u]){
			tam[v] += dfs1(u,v);
		}
	}
	return tam[v];
}
void dfs2(int v,int p,ii &resp){
	int mx = num - tam[v];
	for(int i=0;i<adj[v].size();i++){
		int u = adj[v][i];
		if(u != p && !marcado[u]){
			mx = max(tam[u],mx);
			dfs2(u,v,resp);
		}
	}
	if(mx < resp.first) resp = MP(mx,v);
}
void dfs3(int v,int p,int depth){
	dist[v][++profundidade[v]] = depth;
	for(int i = 0;i < adj[v].size();i++){
		int u = adj[v][i];
		if(u != p && !marcado[u]) dfs3(u,v,depth+1);
	}
}
int find_centroid(int v){
	num = dfs1(v,-1);
	ii resp = NULO;
	dfs2(v,-1,resp);
	dfs3(resp.second,-1,0);
	return resp.second;
}
int decompoe(int v){
	int centroid = find_centroid(v);
	marcado[centroid] = 1;
	for(int i=0;i<adj[centroid].size();i++){
		int u = adj[centroid][i];
		if(marcado[u]) continue;
		u = decompoe(u);
		ctree[u].push_back(centroid);
		ctree[centroid].push_back(u);
	}
	return centroid;
}
void black_to_white(int v){
	cor[v] = 1;
	int x = v;
	for(int depth = profundidade[v];depth>=0;depth--){
		distancias[x].insert(dist[v][depth]);
		x  = pai[x];
	}
}
void white_to_black(int v){
	cor[v] = 0;
	int x = v;
	for(int depth = profundidade[v];depth>=0;depth--){
		distancias[x].erase(distancias[x].find(dist[v][depth]));
		x = pai[x];
	}
}
void dfs_ctree(int v,int p){
	pai[v] = p;
	for(int i=0;i<ctree[v].size();i++){
		int u = ctree[v][i];
		if(u != p){
			dfs_ctree(u,v);
		}
	}
}
int query(int v){
	int resp = MAXN;
	int x = v;
	for(int depth = profundidade[v];depth>=0;depth--){
		if(!distancias[x].empty()){
			int menor = *(distancias[x].begin()) + dist[v][depth];
			resp = min(resp,menor);
		}
		x = pai[x];
	}
	if(resp == MAXN) return -1;
	return resp;
}
int main(){
	int n,q;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		profundidade[i] = -1;
	}
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int raiz = decompoe(1);
	dfs_ctree(raiz,0);
	scanf("%d",&q);
	while(q--){
		int op,v;
		scanf("%d %d",&op,&v);
		if(op == 0){
			if(cor[v] == 0){
				black_to_white(v);
			}
			else{
				white_to_black(v);
			}
		}
		else printf("%d\n",query(v));
	}
	return 0;
}  