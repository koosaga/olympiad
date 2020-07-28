// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1454
#include <cstdio>
#include <algorithm>
#define MAXN 110
#define LIMIT 10000
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
using namespace std;
int n,m,q,matriz[MAXN][MAXN];
int main(){
	int instancia = 1;
	while(true){
		getint(n);
		getint(m);
		if (n == 0 && m == 0) break;
		printf("Instancia %d\n",instancia++);
		for(int i=0;i<=n;i++) for(int j=0;j<=n;j++){
			matriz[i][j] = LIMIT;
		}
		while(m--){
			int u,v,peso;
			getint(u);
			getint(v);
			getint(peso);
			matriz[u][v] = matriz[v][u] = min(peso,matriz[u][v]);
		}
		for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
			matriz[i][j] = min(matriz[i][j],max(matriz[i][k],matriz[k][j]));
		}
		for(int i=0;i<=n;i++) matriz[i][i] = 0;
		getint(q);
		while(q--){
			int origem,destino;
			getint(origem);
			getint(destino);
			printf("%d\n",matriz[origem][destino]);
		}
		printf("\n");
	}
	return 0;
}

