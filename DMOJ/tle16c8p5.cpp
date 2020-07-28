// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle16c8p5
#include <cstdio>
#include <cstring>
#include <vector>
#define MAXN 201
using namespace std;
int vis[MAXN],match[MAXN],pode[MAXN],n,m;
vector<int> grafo[MAXN];
int bipartite(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(int r : grafo[l]){
		if(match[r] == -1){
			match[r] = l;
			return 1;
		}
		else if(bipartite(match[r])){
			match[r] = l;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d %d",&n,&m);
	memset(match,-1,sizeof(match));
	for(int i=1;i<=n;i++){
		int grau;
		scanf("%d",&grau);
		for(int j=1;j<=grau;j++){
			int k;
			scanf("%d",&k);
			if(i == 1){
				pode[k] = 1;
				grafo[1].push_back(k);
			}
			else{
				if(!pode[k]) continue;
				grafo[i].push_back(k);
			}
		}
	}
	int resp = (int)grafo[1].size();
	for(int i=2;i<=n;i++){
		memset(vis,0,sizeof(vis));
		resp -= bipartite(i);
	}
	printf("%d\n",resp);
	return 0;
}