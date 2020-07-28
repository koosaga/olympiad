// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1903
#include <cstdio>
#include <vector>
#include <stack>
#define MAXN 100010
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
int componente[MAXN],ID,processado1[MAXN],processado2[MAXN],V1[10*MAXN],V2[10*MAXN],n,m;
vector<int> grafo[MAXN],transposto[MAXN],novo[MAXN];
vector<vector<int> > matriz;
stack<int> pilha;
void dfs1(int x){
	//printf("DFS1 %d\n",x);
	processado1[x] = 1;
	for(int i = 0; i < grafo[x].size();i++){
		int v = grafo[x][i];
		if(!processado1[v]){
			dfs1(v);
		}
	}
	pilha.push(x);
}
void dfs2(int x){
	//printf("DFS2 %d\n",x);
	processado2[x] = 1;
	componente[x] = ID;
	for(int i=0;i < transposto[x].size();i++){
		int v = transposto[x][i];
		if(!processado2[v]){
			dfs2(v);
		}
	}
}
void dfs_final(int origem,int x){
	matriz[origem][x] = 1;
	for(int i=0;i<novo[x].size();i++){
		int v = novo[x][i];
		if(!matriz[origem][v]){
			dfs_final(origem,v);
		}
	}
}
int main(){
	getint(n);
	getint(m);
	for(int i=1;i<=m;i++){
		getint(V1[i]);
		getint(V2[i]);
		grafo[V1[i]].push_back(V2[i]);
		transposto[V2[i]].push_back(V1[i]);
	}
	for(int i=1;i<=n;i++){
		if(!processado1[i]) dfs1(i);
	}
	while(!pilha.empty()){
		int i = pilha.top();
		pilha.pop();
		if(!processado2[i]){
			ID++;
			dfs2(i);
		}
	}
	vector<int> temp;
	temp.assign(ID+2,0);
	matriz.assign(ID+2,temp);
	for(int i=1;i<=m;i++){
		int u = componente[V1[i]], v = componente[V2[i]];
		if(u == v) continue;
		matriz[u][v] = 1;
	}
	for(int i=1;i<=ID;i++){
		for(int j=1;j<=ID;j++){
			if(matriz[i][j]){
				matriz[i][j] = 0;
				novo[i].push_back(j);
			}
		}
	}
	for(int i=1;i<=ID;i++){
		dfs_final(i,i);
	}
	for(int i=1;i<=ID;i++){
		for(int j=1;j<=ID;j++){
			if(i == j) continue;
			if(!matriz[i][j] && !matriz[j][i]){
				//printf("%d %d\n",i,j);
				printf("Nao Bolada\n");
				return 0;
			}
		}
	}
	printf("Bolada\n");
	return 0;
}
