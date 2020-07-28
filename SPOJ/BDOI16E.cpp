// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BDOI16E/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
vector<ii> grafo[MAXN];
int L1[MAXN],L2[MAXN],L3[MAXN],raiz,sz[MAXN],ac[MAXN],exibir[MAXN],n;
set<int> *conjuntos[MAXN];
void dfs_sack(int v){
	sz[v] = 1;
	int big = -1, mx = -1,ligabig = 0;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first,peso = grafo[v][i].second;
		dfs_sack(u);
		sz[v] += sz[u];
		if(sz[u] > mx){
			mx = sz[u];
			big = u;
			ligabig = peso;
		}
	}
	if(big == -1){
		conjuntos[v] = new set<int>();
		conjuntos[v]->insert(L1[v]);
	}
	else{
		conjuntos[v] = conjuntos[big];
		ac[v] = ac[big] + ligabig;
		conjuntos[v]->insert(L1[v] - ac[v]);
	}
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first,peso = grafo[v][i].second;
		if(u == big) continue;
		for(set<int>::iterator it = conjuntos[u]->begin();it != conjuntos[u]->end();it++){
			int x = *it + peso - ac[v] + ac[u];
			conjuntos[v]->insert(x);
		}
	}
	exibir[v] = (int)conjuntos[v]->size();
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++) scanf("%d",&L1[i]);
	for(int i = 1;i<=n;i++){
		scanf("%d",&L2[i]);
		if(L2[i] == 0) raiz = i;
	}
	for(int i = 1;i<=n;i++){
		scanf("%d",&L3[i]);
		if(L2[i] != 0){
			grafo[L2[i]].push_back(ii(i,L3[i]));
		}
	}
	dfs_sack(raiz);
	for(int i = 1;i<=n;i++) printf("%d\n",exibir[i]);
	return 0;
} 