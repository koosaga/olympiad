// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1344
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAXN 1001
using namespace std;
vector<int> grafo[MAXN];
int grau[MAXN],processado[MAXN],n,p,k,jafoi[MAXN];
int dfs(int x){
	processado[x] = 1;
	int retorna = 1;
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(grau[v] >= k && !processado[v]){
			retorna += dfs(v);
		}
	}
	return retorna;
}
int main(){
	while(scanf("%d %d %d",&n,&p,&k) && (n||p||k)){
		for(int i=1;i<=n;i++){
			grau[i] = 0;
			grafo[i].clear();
			processado[i] = 0;
			jafoi[i] = 0;
		}
		while(p--){
			int u,v;
			scanf("%d %d",&u,&v);
			grau[u]++;
			grau[v]++;
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		for(int vez=1;vez<=n;vez++){
			int menorgrau = -1, davez = -1;
			for(int i=1;i<=n;i++){
				if(jafoi[i]) continue;
				if(menorgrau == -1 || grau[i] < menorgrau){
					davez = i;
					menorgrau = grau[i];
				} 
			}
			if(menorgrau >= k) break;
			for(int i=0;i<grafo[davez].size();i++){
				int proximo = grafo[davez][i];
				grau[davez]--;
				grau[proximo]--;
			}
			jafoi[davez] = 1;
		}
		int resp = 0;
		for(int i=1;i<=n;i++){
			if(grau[i] >= k && !processado[i]){
				resp = max(dfs(i),resp);
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
