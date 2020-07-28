// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2014E/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 1e5 + 1;
vector<int> grafo[MAXN],listas[MAXN];
int nivel[MAXN],nafila[MAXN],processada[MAXN];
long long somatorio;
int maior,pessoas,a,n;
int main(){
	scanf("%d %d",&a,&n);
	for(int vez = 1;vez <= a;vez++){
		int qtd;
		scanf("%d",&qtd);
		while(qtd--){
			int davez;
			scanf("%d",&davez);
			grafo[davez].push_back(vez);
			listas[vez].push_back(davez);
		}
	}
	nafila[1] = 1;
	queue<int> fila;
	fila.push(1);
	while(!fila.empty()){
		int v = fila.front();
		fila.pop();
		maior = max(maior,nivel[v]);
		pessoas++;
		somatorio += (long long)nivel[v];
		for(int i=0;i<grafo[v].size();i++){
			int u = grafo[v][i];
			if(processada[u]) continue;
			processada[u] = 1;
			for(int j = 0; j < listas[u].size();j++){
				int r = listas[u][j];
				if(nafila[r]) continue;
				nafila[r] = 1;
				nivel[r] = nivel[v] + 1;
				fila.push(r); 
			}
		}
	}
	printf("%d %d %lld\n",pessoas,maior,somatorio);
	return 0;
}