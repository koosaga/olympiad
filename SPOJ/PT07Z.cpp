// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PT07Z/
#include <cstdio>
#include <vector>
#define MAXN 10010
using namespace std;
int maior,aux,n;
vector<int> grafo[MAXN];
void dfs(int x,int p,int dist){
	if(dist > maior){
		maior = dist;
		aux = x;
	}
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(v != p){
			dfs(v,x,dist+1);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	dfs(1,-1,0);
	maior = 0;
	dfs(aux,-1,0);
	printf("%d\n",maior);
	return 0;
}