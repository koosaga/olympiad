// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAPATH/
#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 1e4 + 1;
const int MAXL = 1e2 + 1;
const int MAXA = 1e1;
int matriz[MAXL][MAXL];
int id[MAXL][MAXL],cont[MAXA];
int davez,n;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
vector<int> grafo[MAXN][MAXA],match,vis;
int augmenting_path(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(int i = 0;i < grafo[l][davez].size();i++){
		int r = grafo[l][davez][i];
		if(match[r] == -1 || augmenting_path(match[r])){
			match[r] = l;
			return 1;
		}
	}
	return 0;
}
inline int valido(int x,int y){
	return x >= 1 && x <= n && y >= 1 && y <= n;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=1;i<MAXA;i++){
			cont[i] = 0;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&matriz[i][j]);
				cont[matriz[i][j]]++;
				id[i][j] = cont[matriz[i][j]];
				grafo[cont[matriz[i][j]]][matriz[i][j]].clear();
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k = 0;k < 4;k++){
					int ni = i + dx[k];
					int nj = j + dy[k];
					if(valido(ni,nj) && matriz[ni][nj] == matriz[i][j] + 1){
						grafo[id[i][j]][matriz[i][j]].push_back(id[ni][nj]);
					}
				}
			}
		}
		int flag = 0;
		for(davez = 1;davez + 1 < MAXA;davez++){
			match.assign(cont[davez+1] + 2,-1);
			int qtd = 0;
			for(int i = 1;i <= cont[davez] && qtd < cont[davez+1];i++){
				vis.assign(cont[davez]+2,0);
				qtd += augmenting_path(i);
			}
			if(qtd < cont[davez+1]){
				flag = 1;
				break;
			}
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}