// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1227
#include <cstdio>
#include <vector>
#define MAXN 101
using namespace std;
vector<int> grafo[MAXN];
int processado[MAXN],pai[MAXN],nivel[MAXN],N,A,B,C;
void dfs(int x){
	processado[x] = 1;
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(!processado[v]){
			pai[v] = x;
			nivel[v] = nivel[x] + 1;
			dfs(v);
		}
	}
}
int LCA(int u, int v){
	while(u != v){
		if(nivel[u] > nivel[v]){
			u = pai[u];
		}
		else{
			v = pai[v];
		}
	}
	return u;
}
int main(){
	while(scanf("%d %d %d %d",&N,&A,&B,&C) != EOF){
		for(int i=1;i<=N;i++){
			grafo[i].clear();
			pai[i] = -1;
			processado[i] = 0;
			nivel[i] = -1;
		}
		for(int i=1;i<N;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		nivel[A] = 0;
		pai[A] = 0;
		dfs(A);
		int ancestral = LCA(B,C);
		int distb = nivel[B] - nivel[ancestral];
		int distc = nivel[C] - nivel[ancestral];
		double prob = double(distc)/double(distb + distc);
		printf("%.6lf\n",prob);
	}
	return 0;
}
