// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1350
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#define MAXN 1001
using namespace std;
vector<int> verdadeiro[MAXN],falso[MAXN];
int cor[MAXN],n,qtd[2];
char entrada[MAXN];
int main(){
	while(scanf("%d",&n) && n){
		for(int i=1;i<=n;i++){
			verdadeiro[i].clear();
			falso[i].clear();
		}
		for(int i=1;i<=n;i++){
			int davez;
			scanf("%*s %d %*s %s",&davez,entrada);
			if(entrada[0] == 't'){
				verdadeiro[i].push_back(davez);
				verdadeiro[davez].push_back(i);
			}
			else{
				falso[i].push_back(davez);
				falso[davez].push_back(i);
			}
		}
		memset(cor,-1,sizeof(cor));
		int resp = 0;
		int coerente = 1;
		for(int i=1;i<=n && coerente;i++){
			if(cor[i] == -1){
				cor[i] = 1;
				qtd[1] = 1;
				qtd[0] = 0;
				queue<int> bfs;
				bfs.push(i);
				while(!bfs.empty()){
					int v = bfs.front();
					bfs.pop();
					for(int j=0;j<verdadeiro[v].size();j++){
						int u = verdadeiro[v][j];
						if(cor[u] == -1){
							cor[u] = cor[v];
							qtd[cor[u]]++;
							bfs.push(u);
						}
						else if(cor[u] == 1 - cor[v]){
							coerente = 0;
							break;
						}
					}
					for(int j=0;j<falso[v].size();j++){
						int u = falso[v][j];
						if(cor[u] == -1){
							cor[u] = 1 - cor[v];
							qtd[cor[u]]++;
							bfs.push(u);
						}
						else if(cor[u] == cor[v]){
							coerente = 0;
							break;
						}
					}
				}
				resp += max(qtd[0],qtd[1]);
			}
		}
		if(coerente) printf("%d\n",resp);
		else printf("Inconsistent\n");
	}
	return 0;
}
