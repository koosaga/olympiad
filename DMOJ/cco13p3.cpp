// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco13p3
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define MAXN 400010
using namespace std;
typedef map<int,int>::iterator ite;
vector<int> grafo[MAXN];
map<int,int> *conjunto[MAXN];
int aux,maioral,n,tam[MAXN],diametro,nivel[MAXN],ac[MAXN];
long long resp;
void dfs_diametro(int v,int p,int depth){
	if(depth > maioral){
		maioral = depth;
		aux = v;
	}
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs_diametro(u,v,depth+1);
	}
}
void dfs_sack(int v,int p){
	tam[v] = 1;
	int mx = -1, big = -1;
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs_sack(u,v);
		tam[v] += tam[u];
		if(tam[u] > mx){
			mx = tam[u];
			big = u;
		}
	}
	if(big == -1){
		conjunto[v] = new map<int,int>();
		(*conjunto[v])[0] = 1;
		return;
	}
	else{
		ac[v] = ac[big] + 1;
		conjunto[v] = conjunto[big];
		if((*conjunto[v]).count(diametro - ac[v])) resp += 1LL*(*conjunto[v])[diametro - ac[v]];
		(*conjunto[v])[-ac[v]] = 1;
	}
	for(int u : grafo[v]){
		if(u == p || u == big) continue;
		for(ite it = conjunto[u]->begin();it != conjunto[u]->end();it++){
			int dist = (*it).first + 1 + ac[u];
			int qtd = (*it).second;
			if((*conjunto[v]).count(diametro - dist - ac[v])) resp += 1LL*qtd * (*conjunto[v])[diametro - dist - ac[v]];
		}
		for(ite it = conjunto[u]->begin();it != conjunto[u]->end();it++){
			int dist = (*it).first + 1  + ac[u];
			int qtd = (*it).second;
			(*conjunto[v])[dist - ac[v]] += qtd;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	dfs_diametro(1,-1,0);
	maioral = 0;
	dfs_diametro(aux,-1,0);
	diametro = maioral;
	dfs_sack(1,-1);
	printf("%d %lld\n",diametro + 1,resp);
	return 0;
}urn 0;
}