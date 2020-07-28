// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADATRIP/
#include <cstdio>
#include <vector>
#include <stack>
#define MAXN 500010
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<ii> grafo[MAXN];
stack<int> pilha[10*MAXN];
int processado[MAXN],atual,qtd,tamanho,n,m,q,respatual,respqtd;
int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		grafo[u].push_back(MP(v,peso));
		grafo[v].push_back(MP(u,peso));
	}
	for(int vez = 1;vez <= q;vez++){
		int ini;
		scanf("%d",&ini);
		pilha[0].push(ini);
		tamanho = 1;
		atual = 0;
		qtd = 0;
		respatual = 0;
		respqtd = 0;
		while(tamanho > 0){
			while(pilha[atual].empty()){
				atual++;
				qtd = 0;
			}
			while(!pilha[atual].empty()){
				int  v = pilha[atual].top();
				pilha[atual].pop();
				tamanho--;
				if(processado[v] == vez) continue;
				processado[v] = vez;
				respatual = atual;
				qtd++;
				respqtd = qtd;
				for(int i=0;i<grafo[v].size();i++){
					int u = grafo[v][i].first, peso = grafo[v][i].second;
					if(processado[u] == vez) continue;
					pilha[atual+peso].push(u); 
					tamanho++;
				}
			}
		}
		printf("%d %d\n",respatual,respqtd);
	}
	return 0;
}