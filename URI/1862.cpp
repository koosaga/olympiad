// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1862
#include <cstdio>
#include <vector>
#define MAXN 1001
using namespace std;
int componente[MAXN],componentes,numero[MAXN],counting[MAXN],n;
char entrada[MAXN][MAXN];
vector<int> grafo[MAXN];
void dfs(int v){
	componente[v] = componentes;
	numero[componentes]++;
	for(int i=0;i<grafo[v].size();i++){
		int u = grafo[v][i];
		if(!componente[u]){
			dfs(u);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",entrada[i]);
		for(int j=0;j<n;j++){
			if(entrada[i][j] == 'S' && i != j){
				grafo[i].push_back(j);
			}
		}
	}
	for(int i=0;i<n;i++){
		if(!componente[i]){
			componentes++;
			dfs(i);
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(entrada[i][j] == 'D' && componente[i] == componente[j]){
				printf("-1\n");
				return 0;
			}
		}
	}
	printf("%d\n",componentes);
	for(int i=1;i <= componentes;i++){
		counting[numero[i]]++;
	}
	int first = 0;
	for(int i=1000;i>0;i--){
		while(counting[i]--){
			if(first) printf(" ");
			else first = 1;
			printf("%d",i);
		}
	}
	printf("\n");
	return 0;
}
