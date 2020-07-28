// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1128
#include <cstdio>
#include <vector>
#define MAX 2020
#define PB push_back
using namespace std;
typedef vector<int> vi;
int visitado[MAX],n,m;
vi grafo[MAX],transposto[MAX];
int dfs1(int u){
	visitado[u]=1;
	int retornar = 1;
	for(vi::iterator it=grafo[u].begin();it!=grafo[u].end();it++){
		int v = *it;
		if (!visitado[v]){
			retornar += dfs1(v);
		}
	}
	return retornar;
}
int dfs2(int u){
	visitado[u]=0;
	int retornar = 1;
	for(vi::iterator it=transposto[u].begin();it!=transposto[u].end();it++){
		int v = *it;
		if (visitado[v]){
			retornar += dfs2(v);
		}
	}
	return retornar;
}
int main(){
	while(1){
		scanf("%d %d",&n,&m);
		if (n==0 && m == 0) break;
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			transposto[i].clear();
			visitado[i]=0;
		}
		for(int i=0;i<m;i++){
			int origem,destino,mao;
			scanf("%d %d %d",&origem,&destino,&mao);
			if (mao==2) {
				grafo[origem].PB(destino);
				transposto[destino].PB(origem);
				grafo[destino].PB(origem);
				transposto[origem].PB(destino);
			}
			else {
				grafo[origem].PB(destino);
				transposto[destino].PB(origem);
			} 
		}
		if (dfs1(1)!=n) {
			printf("0\n");
			continue;
		}
		if (dfs2(1)!=n){
			printf("0\n");
			continue;
		}
		printf("1\n");
	}
	return 0;
}
