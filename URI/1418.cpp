// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1418
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define MAXN 100010
using namespace std;
int n,t;
vector<int> grafo[MAXN];
int dfs(int x){
	if(grafo[x].size() == 0) return 1;
	vector<int> menores;
	int temqueter = ceil(grafo[x].size() * t * 0.01);
	int retorna = 0;
	for(int i=0;i<grafo[x].size();i++){
		menores.push_back(dfs(grafo[x][i]));
	}
	sort(menores.begin(),menores.end());
	for(int i=0;i<temqueter;i++){
		retorna += menores[i];
	}
	return retorna;
}
int main(){
	while(scanf("%d %d",&n,&t) && (n||t)){
		for(int i=0;i<=n;i++){
			grafo[i].clear();
		}
		for(int i=1;i<=n;i++){
			int chefe;
			scanf("%d",&chefe);
			grafo[chefe].push_back(i);
		}
		printf("%d\n",dfs(0));
	}
	return 0;
}
