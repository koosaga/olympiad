// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1821
#include <cstdio>
#include <vector>
#include <unordered_set>
#define MAXN 201
using namespace std;
vector<int> grafo[MAXN],match,vis;
unordered_set<int> proibido[MAXN];
int augmenting_path(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(int i = 0; i < grafo[l].size();i++){
		int r = grafo[l][i];
		if(match[r] == -1 || augmenting_path(match[r])){
			match[r] = l;
			return 1;
		}
	}
	return 0;
}
int main(){
	int n,m,instancia = 1;
	while(scanf("%d %d",&n,&m) && (n || m)){
		printf("Instancia %d\n",instancia++);
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			proibido[i].clear();
		}
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			proibido[u].insert(v);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(proibido[i].count(j)) continue;
				grafo[i].push_back(j+n);
			}
		}
		match.assign(2*n+10,-1);
		int resp = 0;
		for(int i=1;i<=n;i++){
			vis.assign(n+10,0);
			resp += augmenting_path(i);
		}
		if(resp == n) printf("possivel\n");
		else printf("impossivel\n");
		printf("\n");
	}
	return 0;
}
