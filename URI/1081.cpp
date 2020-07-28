// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1081
#include <cstdio>
#include <cstring>
#define MAXN 21
int processado[MAXN],matriz[MAXN][MAXN];
void dfs(int v,int espacos){
	processado[v] = 1;
	int hehe = 0;
	for(int i=0;i<=20;i++){
		if(matriz[v][i] == 1 && !processado[i]){
			for(int j=0;j<espacos;j++){
				printf(" ");
			}
			printf("%d-%d pathR(G,%d)\n",v,i,i);
			dfs(i,espacos+2);
			hehe = 1;
		}
		else if(matriz[v][i] == 1 && processado[i]){
			for(int j=0;j<espacos;j++){
				printf(" ");
			}
			printf("%d-%d\n",v,i);
			hehe = 1;
		}
	}
	if(espacos == 2 && hehe) printf("\n");
}
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc=1;tc<=TC;tc++){
		printf("Caso %d:\n",tc);
		memset(processado,0,sizeof(processado));
		memset(matriz,0,sizeof(matriz));
		int v,e;
		scanf("%d %d",&v,&e);
		while(e--){
			int p,q;
			scanf("%d %d",&p,&q);
			matriz[p][q] = 1;
		}
		for(int i=0;i<v;i++){
			if(!processado[i]) dfs(i,2);
		}
	}
	return 0;
}
