// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1490
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 1e3 + 1;
typedef vector<int> vi;
typedef set<int> si;
vector<vi> processado;
vector<si> grafo;
vi match,vis;
char mapa[MAXN][MAXN];
int idcoluna[MAXN][MAXN],idlinha[MAXN][MAXN];
int V,n,m;
int augmenting_path(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(auto it = grafo[l].begin();it != grafo[l].end();it++){
		int r = *it;
		if(match[r] == -1 || augmenting_path(match[r])){
			match[r] = l;
			return 1;
		}
	}
	return 0;
}
int main(){
	while(scanf("%d",&V) != EOF){
		grafo.clear();
		match.clear();
		vis.clear();
		n = 0;
		m = 0;
		for(int i=0;i<V;i++){
			scanf("%s",mapa[i]);
		}
		vi temp;
		temp.assign(V+1,0);
		processado.assign(V+1,temp);
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
				if(mapa[i][j] == '.'){
					while(j < V && mapa[i][j] == '.'){
						idlinha[i][j] = n;
						j++;
					}
					n++;
				}
			}
		}
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
				if(mapa[i][j] == '.' && !processado[i][j]){
					int k = i;
					while(k < V && mapa[k][j] == '.'){
						idcoluna[k][j] = m;
						processado[k][j] = 1;
						k++;
					}
					m++;
				}
			}
		}
		si vazio;
		grafo.assign(n+m+1,vazio);
		match.assign(n+m+1,-1);
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
				if(mapa[i][j] == '.'){
					grafo[idlinha[i][j]].insert(idcoluna[i][j]);
					//printf("%d vai %d\n",idlinha[i][j],idcoluna[i][j]);
				}
			}
		}
		int resp = 0;
		for(int i=0;i<n;i++){
			vis.assign(n+m+1,0);
			resp += augmenting_path(i);
		}
		printf("%d\n",resp);
	}
	return 0;
}

