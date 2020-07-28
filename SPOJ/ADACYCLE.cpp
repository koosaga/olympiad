// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACYCLE/
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#define MP make_pair
#define MAXN 2001
using namespace std;
typedef pair<int,int> ii;
vector<int> original[MAXN],transposto[MAXN],grafo[MAXN];
stack<int> pilha;
int processado[MAXN],n,processado1[MAXN],processado2[MAXN],componente,meucompomente[MAXN];
void dfs1(int x){
	processado1[x] = 1;
	for(int i = 0;i < original[x].size();i++){
		int v = original[x][i];
		if(!processado1[v]) dfs1(v);
	}
	pilha.push(x);
}
void dfs2(int x){
	processado2[x] = 1;
	meucompomente[x] = componente;
	for(int i = 0;i < transposto[x].size();i++){
		int v = transposto[x][i];
		if(!processado2[v]) dfs2(v);
	} 
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int davez;
			scanf("%d",&davez);
			if(davez == 1){
				original[i].push_back(j);
				transposto[j].push_back(i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!processado1[i]) dfs1(i);
	}
	while(!pilha.empty()){
		int i = pilha.top();
		pilha.pop();
		if(!processado2[i]){
			componente++;
			dfs2(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j = 0;j < original[i].size();j++){
			int k = original[i][j];
			if(meucompomente[i] != meucompomente[k]) continue;
			grafo[i].push_back(k);
		}
	}
	for(int i=1;i<=n;i++){
		queue<ii> bfs;
		for(int j = 0;j < grafo[i].size();j++){
			bfs.push(MP(grafo[i][j],1));
			processado[grafo[i][j]] = i;
		}
		int flag = 0;
		if(processado[i] == i){
			printf("1\n");
			continue;
		}
		while(!bfs.empty()){
			int v = bfs.front().first, d = bfs.front().second;
			bfs.pop();
			if(v == i){
				printf("%d\n",d);
				flag = 1;
				break;
			}
			for(int j = 0;j < grafo[v].size();j++){
				int u = grafo[v][j];
				if(processado[u] != i){
					processado[u] = i;
					if(u == i){
						printf("%d\n",d+1);
						flag = 1;
						break;
					}
					bfs.push(MP(u,d+1));
				}
			}
		}
		if(!flag) printf("NO WAY\n");
	}
	return 0;
}