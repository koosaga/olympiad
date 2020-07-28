// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BUGLIFE/
#include <cstdio>
#include <vector>
#include <queue>
#define MAXN 2010
using namespace std;
vector<int> grafo[MAXN];
int cor[MAXN],TC,n,m;
int main(){
	scanf("%d",&TC);
	for(int tc = 1;tc <= TC;tc++){
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			cor[i] = -1;
		}
		while(m--){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		int isBipartite = 1;
		for(int i=1;i<=n;i++){
			if(cor[i] == -1){
				cor[i] = 1;
				queue<int> bfs;
				bfs.push(i);
				while(!bfs.empty()){
					int v = bfs.front();
					bfs.pop();
					for(int u : grafo[v]){
						if(cor[u] == -1){
							cor[u] = 1 - cor[v];
							bfs.push(u);
						}
						else if(cor[u] == cor[v]){
							isBipartite = 0;
						}
					}
				}
			}
		}
		printf("Scenario #%d:\n",tc);
		if(isBipartite) printf("No suspicious bugs found!\n");
		else printf("Suspicious bugs found!\n");
	}
	return 0;
}