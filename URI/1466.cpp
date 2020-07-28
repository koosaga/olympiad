// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1466
#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 503
using namespace std;
int ID,valor[MAXN],esquerda[MAXN],direita[MAXN],TC,n;
void insere(int raiz, int val){
	if(val < valor[raiz]){
		if(esquerda[raiz] == -1){
			esquerda[raiz] = ++ID;
			valor[ID] = val;
			return;
		}
		else{
			insere(esquerda[raiz],val);
			return;
		}
	}
	else{
		if(direita[raiz] == -1){
			direita[raiz] = ++ID;
			valor[ID] = val;
			return;
		}
		else{
			insere(direita[raiz],val);
			return;
		}
	}
}
int main(){
	scanf("%d",&TC);
	for(int tc = 1; tc <= TC; tc++){
		printf("Case %d:\n",tc);
		ID = 1;
		scanf("%d",&n);
		for(int i=0;i<=n;i++){
			esquerda[i] = direita[i] = -1;
		}
		scanf("%d",&valor[1]);
		for(int i=2;i<=n;i++){
			int davez;
			scanf("%d",&davez);
			insere(1,davez);
		}
		queue<int> bfs;
		bfs.push(1);
		while(!bfs.empty()){
			int v = bfs.front();
			bfs.pop();
			if(v == -1) continue;
			if(v != 1) printf(" ");
			printf("%d",valor[v]);
			bfs.push(esquerda[v]);
			bfs.push(direita[v]);
		}
		printf("\n\n");
	}
	return 0;
}
