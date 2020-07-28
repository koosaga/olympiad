// Ivan Carvalho
// Solution to https://www.spoj.com/problems/IMPER/
#include <cstdio>
#include <vector>
#define MAXN 10010
using namespace std;
int processado[MAXN],n,anterior,maximo,aux;
vector<int> grafo[MAXN];
void dfs(int v, int percorrido){
	processado[v] = 1;
	if (percorrido > maximo){
		aux = v;
		maximo = percorrido;
	}
	for(int i =0;i <grafo[v].size();i++){
		int u = grafo[v][i];
		if (!processado[u]){
			dfs(u,percorrido+1);
		}
	}
}
int main(){
	while(scanf("%d",&n) && n != -1){
		maximo = 0;
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			processado[i] = 0;
		}
		for(int i=2;i<=n;i++){
			scanf("%d",&anterior);
			grafo[anterior].push_back(i);
			grafo[i].push_back(anterior);
		}
		dfs(1,0);
		for(int i=1;i<=n;i++) processado[i] = 0;
		maximo = 0;
		dfs(aux,0);
		printf("%d\n",(maximo+1)/2);
	}
	return 0;
}