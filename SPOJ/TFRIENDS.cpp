// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TFRIENDS/
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;
#define MAXN 110
#define PB push_back
typedef vector<int> vi;
int visitado[MAXN],n,casos;
vi grafo[MAXN],transposto[MAXN];
stack<int> pilha;
void dfs1(int u){
	visitado[u]=1;
	for(vi::iterator it=grafo[u].begin();it!=grafo[u].end();it++){
		int v = *it;
		if (!visitado[v]) {
			dfs1(v);
		}
	}
	pilha.push(u);
}
void dfs2(int u){
	visitado[u]=0;
	for(vi::iterator it=transposto[u].begin();it!=transposto[u].end();it++){
		int v = *it;
		if (visitado[v]) {
			dfs2(v);
		}
	}
}
int main(){
	scanf("%d",&casos);
	while(casos--){
		int resposta = 0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			grafo[i].clear();
			transposto[i].clear();
			visitado[i]=0;
		}
		for(int i=0;i<n;i++){
			char davez[MAXN];
			scanf("%s",davez);
			for(int j=0;j<n;j++){
				if (davez[j] == 'Y'){
					grafo[i].PB(j);
					transposto[j].PB(i);
				}
			}
		}
		for(int i=0;i<n;i++) if (!visitado[i]) dfs1(i);
		while(!pilha.empty()){
			int atual = pilha.top();
			pilha.pop();
			if (visitado[atual]) {
				dfs2(atual);
				resposta++;
			}
		}
		printf("%d\n",resposta);
	}
	return 0;
}