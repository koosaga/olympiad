// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DISQUERY/
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAXN 100010
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<ii> grafo[MAXN];
int pai[MAXN],superpai[MAXN],nivel[MAXN],estrela[MAXN],segmento,n;
ii ligapai[MAXN],ligasuperpai[MAXN];
void dfs_pai(int x){
	for(int i = 0;i<grafo[x].size();i++){
		int v = grafo[x][i].first;
		if(pai[v] == -1){
			pai[v] = x;
			ligapai[v] = MP(grafo[x][i].second,grafo[x][i].second);
			nivel[v] = nivel[x] + 1;
			dfs_pai(v);
		}
	}
}
void dfs_superpai(int x,int p){
	superpai[x] = p;
	if(nivel[x] % segmento == 0){
		p = x;
		estrela[x] = 1;
	}
	for(int i = 0;i<grafo[x].size();i++){
		int v = grafo[x][i].first;
		if(superpai[v] == -1){
			dfs_superpai(v,p);
		}
	}
}
ii LCA(int u,int v){
	int maior = -1, menor = 1e9 + 1;
	while(superpai[u] != superpai[v]){
		if(nivel[u] > nivel[v]){
			if(!estrela[u]){
				menor = min(ligapai[u].first,menor);
				maior = max(ligapai[u].second,maior);
				u = pai[u];
			}
			else{
				menor = min(ligasuperpai[u].first,menor);
				maior = max(ligasuperpai[u].second,maior);
				u = superpai[u];
			}
		}
		else{
			if(!estrela[v]){
				menor = min(ligapai[v].first,menor);
				maior = max(ligapai[v].second,maior);
				v = pai[v];
			}
			else{
				menor = min(ligasuperpai[v].first,menor);
				maior = max(ligasuperpai[v].second,maior);
				v = superpai[v];
			}
		}
	}
	while(u != v){
		if(nivel[u] > nivel[v]){
			menor = min(ligapai[u].first,menor);
			maior = max(ligapai[u].second,maior);
			u = pai[u];
		}
		else{
			menor = min(ligapai[v].first,menor);
			maior = max(ligapai[v].second,maior);
			v = pai[v];
		}
	}
	return MP(menor,maior);
}
int main(){
	scanf("%d",&n);
	segmento = 1;
	for(int i=1;i<=n;i++){
		pai[i] = superpai[i] = -1;
	}
	for(int i=1;i<n;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		grafo[u].push_back(MP(v,peso));
		grafo[v].push_back(MP(u,peso));
	}
	nivel[1] = 0;
	pai[1] = 1;
	superpai[1] = 1;
	ligapai[1] = MP(1000000001,-1);
	dfs_pai(1);
	for(int i=1;i<=n;i++) segmento = max(segmento,nivel[i]);
	segmento = sqrt(segmento);
	dfs_superpai(1,1);
	for(int i=1;i<=n;i++){
		if(!estrela[i]) continue;
		int alvo = superpai[i];
		int menor = 1e9 + 1, maior = -1;
		int temp = i;
		while(temp != alvo){
			menor = min(ligapai[temp].first,menor);
			maior = max(ligapai[temp].second,maior);
			temp = pai[temp];
		}
		ligasuperpai[i] = MP(menor,maior);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int u,v,peso;
		scanf("%d %d",&u,&v);
		ii resp = LCA(u,v);
		printf("%d %d\n",resp.first,resp.second);
	}
	return 0;
}