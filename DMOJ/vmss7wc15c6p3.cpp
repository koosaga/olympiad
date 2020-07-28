// Ivan Carvalho
// Solution to https://dmoj.ca/problem/vmss7wc15c6p3
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 400010;
int numero[MAXN];
vector<int> grafo[MAXN];
void dfs(int v,int p){
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs(u,v);
		numero[v] += numero[u];
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&numero[i]);
	dfs(1,-1);
	int resp = numero[1];
	for(int i=2;i<=n;i++) resp = max(resp,numero[i]);
	printf("%d\n",resp);
	return 0;
}