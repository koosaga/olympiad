// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1835
#include <cstdio>
#define MAXN 110
int pai[MAXN],peso[MAXN],t,n,m,conjuntos,caso;
int find(int x){
	if (x==pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if (x==y) return;
	conjuntos--;
	if (peso[x]<peso[y]) pai[x] = y;
	else if (peso[y]<peso[x]) pai[y] = x;
	else{
		pai[x] = y;
		peso[y]++;
	}
}
int main(){
	scanf("%d",&t);
	for(caso=1;caso<=t;caso++){
		scanf("%d %d",&n,&m);
		conjuntos = n-1;
		for(int i=1;i<=n;i++) {
			peso[i] = 0;
			pai[i] = i;
		}
		while(m--){
			int u,v;
			scanf("%d %d",&u,&v);
			join(u,v);
		}
		if (!conjuntos) printf("Caso #%d: a promessa foi cumprida\n",caso);
		else printf("Caso #%d: ainda falta(m) %d estrada(s)\n",caso,conjuntos);
	}
	return 0;
}
