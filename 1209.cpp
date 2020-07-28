// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1209
#include <cstdio>
#define MAXN 1001
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
int grau[MAXN],processado[MAXN],grafo[MAXN][MAXN],tamanho[MAXN];
int main(){
	int n,m,k;
	while(scanf("%d %d %d",&n,&m,&k) != EOF){
		int possivel = 0;
		for(int i=1;i<=n;i++){
			grau[i] = 0;
			processado[i] = 0;
			tamanho[i] = 0;
		}
		while(m--){
			int u,v;
			getint(u);
			getint(v);
			grau[u]++;
			grau[v]++;
			grafo[u][tamanho[u]++] = v;
			grafo[v][tamanho[v]++] = u;
		}
		for(int contador = 0; contador < n;contador++){
			int vertice = -1, graumaximo = n + 20;
			for(int i=1;i<=n;i++){
				if(processado[i]) continue;
				if(grau[i] < graumaximo){
					graumaximo = grau[i];
					vertice = i;
				}
			}
			processado[vertice] = 1;
			if(graumaximo >= k) break;
			for(int i = 0; i < tamanho[vertice];i++){
				int u = grafo[vertice][i];
				grau[u]--;
			}
		}
		for(int i=1;i<=n;i++){
			if(grau[i] >= k){
				if(possivel) printf(" ");
				else possivel = 1;
				printf("%d",i);
			}
		}
		if(possivel == 0) printf("0");
		printf("\n");
	}
	return 0;
}
