// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1208
#include <cstdio>
#include <vector>
#define MAXN 2001
using namespace std;
int n,m;
vector<int> grafo[MAXN],vis,match;
int augmenting_path(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(int i=0;i<grafo[l].size();i++){
		int r = grafo[l][i];
		if(match[r] == -1 || augmenting_path(match[r])){
			match[r] = l;
			return 1;
		}
	} 
	return 0;
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		for(int i=1;i<=n;i++){
			grafo[i].clear();
		}
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v+n);
		}
		int resp = n;
		match.assign(2*n+2,-1);
		for(int i=1;i<=n;i++){
			vis.assign(n+2,0);
			resp -= augmenting_path(i);
		}
		printf("%d\n",resp);
	}
	return 0;
}
