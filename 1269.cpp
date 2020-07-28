// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1269
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define MAXN 1001
using namespace std;
vector<int> grafo[MAXN],novo_grafo[MAXN],tarefas[MAXN],novas_tarefas[MAXN];
int grau[MAXN],processado[MAXN],marcado[MAXN],valor[MAXN],novo_valor[MAXN],dp[MAXN],conversao[MAXN],reverso[MAXN],n,m,contador;
int dfs1(int x){
	if(dp[x] != -1) return dp[x];
	dp[x] = novo_valor[x];
	for(int i=0;i<novo_grafo[x].size();i++){
		int v = novo_grafo[x][i];
		dp[x] += dfs1(v);
	}
	return dp[x];
}
void dfs2(int x){
	processado[x] = 1;
	for(int i=0;i<novo_grafo[x].size();i++){
		int v = novo_grafo[x][i];
		if(!processado[v]){
			marcado[v] = 1;
			dfs2(v);
		}
	}
}
int main(){
	while(scanf("%d %d",&n,&m) && (n||m)){
		//printf("%d %d\n",n,m);
		for(int i=1;i<=max(n,m);i++){
			grafo[i].clear();
			novo_grafo[i].clear();
			tarefas[i].clear();
			novas_tarefas[i].clear();
			processado[i] = 0;
			marcado[i] = 0;
			valor[i] = 0;
			novo_valor[i] = 0;
			grau[i] = 0;
			conversao[i] = 0;
			reverso[i] = 0;
			dp[i] = -1;
		}
		contador = 0;
		for(int i=1;i<=n;i++){
			int qtd1,qtd2;
			scanf("%d %d %d",&valor[i],&qtd1,&qtd2);
			//printf("%d %d %d\n",valor[i],qtd1,qtd2);
			while(qtd1--){
				int davez;
				scanf("%d",&davez);
				//printf("%d %d\n",i,davez);
				grafo[i].push_back(davez);
				grau[davez]++;
			}
			while(qtd2--){
				int davez;
				scanf("%d",&davez);
				//printf("%d %d\n",i,davez);
				tarefas[davez].push_back(i);
			}
		}
		queue<int> bfs;
		for(int i=1;i<=n;i++){
			if(grau[i] == 0) bfs.push(i);
		}
		while(!bfs.empty()){
			int v = bfs.front();
			bfs.pop();
			conversao[v] = ++contador;
			reverso[contador] = v;
			for(int i=0;i<grafo[v].size();i++){
				int u = grafo[v][i];
				grau[u]--;
				if(!grau[u]) bfs.push(u);
			} 
		}
		for(int i=1;i<=n;i++){
			int antigo = reverso[i];
			novo_grafo[i] = grafo[antigo];
			for(int j=0;j<novo_grafo[i].size();j++){
				novo_grafo[i][j] = conversao[novo_grafo[i][j]];
			}
			sort(novo_grafo[i].begin(),novo_grafo[i].end());
			novo_valor[i] = valor[antigo];
		}
		for(int i=1;i<=n;i++) dfs1(i);
		printf("*****\n");
		for(int i=1;i<=m;i++){
			novas_tarefas[i] = tarefas[i];
			for(int j=0;j<novas_tarefas[i].size();j++){
				novas_tarefas[i][j] = conversao[novas_tarefas[i][j]];
			}
			sort(novas_tarefas[i].begin(),novas_tarefas[i].end());
			int resp = 0;
			memset(processado,0,sizeof(processado));
			memset(marcado,0,sizeof(marcado));
			for(int j=0;j<novas_tarefas[i].size();j++){
				int v = novas_tarefas[i][j];
				if(!processado[v]) dfs2(v);
			}
			for(int j=0;j<novas_tarefas[i].size();j++){
				int v = novas_tarefas[i][j];
				resp += (1 - marcado[v])*dfs1(v);
			}
			printf("%d %d\n",i,resp);
		}
	}
	return 0;
}
