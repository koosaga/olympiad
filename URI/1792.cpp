// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1792
#include <cstdio>
#include <queue>
#include <vector>
#define MAXN 10010
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<int> grafo[MAXN];
int inimigos[MAXN],refens[MAXN],grau[MAXN],n,m,s;
int main(){
	while(scanf("%d %d %d",&n,&m,&s) && (n||m||s)){
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			grau[i] = inimigos[i] = refens[i] = 0; 
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&inimigos[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&refens[i]);
		}
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grau[v]++;
		}
		int processados = 0;
		priority_queue<ii, vector<ii>, greater<ii> > fila;
		for(int i=1;i<=n;i++){
			if(grau[i] == 0) fila.push(MP(inimigos[i],i));
		}
		while(!fila.empty()){
			ii escolhido = fila.top();
			fila.pop();
			int rivais = escolhido.first, v = escolhido.second;
			if(rivais >= s){
				break;
			}
			s += refens[v];
			processados++;
			for(int i=0;i<grafo[v].size();i++){
				int u = grafo[v][i];
				grau[u]--;
				if(grau[u] == 0) fila.push(MP(inimigos[u],u));
			}
		}
		if(processados == n) printf("possivel\n");
		else printf("impossivel\n");
	}
	return 0;
}
