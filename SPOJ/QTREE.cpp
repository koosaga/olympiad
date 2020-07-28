// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QTREE/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#define MAXN 10010
using namespace std;
int pai[MAXN],superpai[MAXN],nivel[MAXN],ligapai[MAXN],n,segmento,estrela[MAXN],A[MAXN],B[MAXN],C[MAXN];
char entrada[200];
multiset<int> conjunto[MAXN];
vector<int> grafo[MAXN],original[MAXN],dependepai[MAXN];
void dfs_pai(int x){
	//printf("X : %d\n",x);
	for(int i = 0;i < grafo[x].size();i++){
		int v = grafo[x][i];
		if(pai[v] == -1){
			pai[v] = x;
			ligapai[v] = original[x][i];
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
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(superpai[v] == -1){
			dfs_superpai(v,p);
		}
	}
}
int LCA(int u,int v){
	if(u == v) return 0;
	int resp = -1;
	while(superpai[u] != superpai[v]){
		if(nivel[u] > nivel[v]){
			if(!estrela[u]){
				resp = max(ligapai[u],resp);
				u = pai[u];
				continue;
			}
			resp = max(resp, *conjunto[u].rbegin() );
			u = superpai[u];
		}
		else{
			if(!estrela[v]){
				resp = max(ligapai[v],resp);
				v = pai[v];
				continue;
			}
			resp = max(resp, *conjunto[v].rbegin() );
			v = superpai[v];
		}
	}
	while(u != v){
		if(nivel[u] > nivel[v]){
			resp = max(resp,ligapai[u]);
			u = pai[u];
		}
		else{
			resp = max(resp,ligapai[v]);
			v = pai[v];
		}
	}
	return resp;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		segmento = sqrt(n);
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			original[i].clear();
			dependepai[i].clear();
			conjunto[i].clear();
			pai[i] = superpai[i] = -1;
			estrela[i] = 0;
		}
		for(int i=1;i<n;i++){
			scanf("%d %d %d",&A[i],&B[i],&C[i]);
			grafo[A[i]].push_back(B[i]);
			original[A[i]].push_back(C[i]);
			grafo[B[i]].push_back(A[i]);
			original[B[i]].push_back(C[i]);
		}
		nivel[1] = 0;
		pai[1] = 1;
		superpai[1] = 1;
		dfs_pai(1);
		//printf("Pai\n");
		//printf("Segmento %d\n",segmento);
		dfs_superpai(1,1);
		//printf("Superpai\n");
		for(int i=1;i<=n;i++){
			if(!estrela[i]) continue;
			int alvo = superpai[i];
			int temp = i;
			while(temp != alvo){
				conjunto[i].insert(ligapai[temp]);
				dependepai[temp].push_back(i);
				temp = pai[temp];
			}
		}
		//printf("Estrelas\n");
		for(int i=1;i<n;i++){
			if(nivel[A[i]] < nivel[B[i]]) swap(A[i],B[i]);
		}
		while(true){
			scanf("%s",entrada);
			//printf("%s\n",entrada);
			if(entrada[0] == 'D') break;
			if(entrada[0] == 'Q'){
				int a,b;
				scanf("%d %d",&a,&b);
				printf("%d\n",LCA(a,b));
			}
			if(entrada[0] == 'C'){
				int ith,val;
				scanf("%d %d",&ith,&val);
				int i = A[ith];
				int oldval = ligapai[i];
				for(int j=0;j<dependepai[i].size();j++){
					int u = dependepai[i][j];
					conjunto[u].erase(conjunto[u].find(oldval));
					conjunto[u].insert(val);
				}
				ligapai[i] = val;
			}
		}
	}
	return 0;
} 