// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c3p5
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 3*1e5 + 10;
const int MAXL = 19;
int ancestral[MAXN][MAXL];
int nivel[MAXN];
int raiz[MAXN];
int representa[MAXN];
int ptr;
int LCA(int u,int v){
	if(nivel[u] < nivel[v]) swap(u,v);
	for(int i = MAXL - 1;i>=0;i--){
		if(ancestral[u][i] != -1 && nivel[ancestral[u][i]] >= nivel[v]){
			u = ancestral[u][i];
		}
	}
	if(u == v) return u;
	for(int i = MAXL - 1;i >= 0;i--){
		if(ancestral[u][i] != -1 && ancestral[u][i] != ancestral[v][i]){
			u = ancestral[u][i];
			v = ancestral[v][i];
		}
	}
	return ancestral[u][0];
}
int main(){
	memset(ancestral,-1,sizeof(ancestral));
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		char op;
		scanf(" %c",&op);
		if(op == 'a'){
			int v;
			scanf("%d",&v);
			raiz[i] = ++ptr;
			representa[ptr] = i;
			ancestral[ptr][0] = raiz[v];
			nivel[ptr] = nivel[raiz[v]] + 1;
			for(int j=1;j<MAXL;j++){
				if(ancestral[ptr][j-1] != -1) ancestral[ptr][j] = ancestral[ancestral[ptr][j-1]][j-1];
			}
		}
		else if(op == 'b'){
			int v;
			scanf("%d",&v);
			raiz[i] = ancestral[raiz[v]][0];
			printf("%d\n",representa[raiz[v]]);
		}
		else if(op == 'c'){
			int v,w;
			scanf("%d %d",&v,&w);
			raiz[i] = raiz[v];
			v = raiz[v];
			w = raiz[w];
			printf("%d\n",nivel[LCA(w,v)]);
		}
	}
	return 0;
}