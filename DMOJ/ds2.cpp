// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ds2
#include <cstdio>
#define MAXN 100010
int peso[MAXN],pai[MAXN],resposta[MAXN],vertice,conjuntos,n,m;
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	if(peso[x] < peso[y]){
		pai[x] = y;
	}
	else if(peso[y] > peso[x]){
		pai[y] = x;
	}
	else{
		pai[x] = y;
		peso[y]++;
	}
}
int main(){
	scanf("%d %d",&n,&m);
	conjuntos = n;
	for(int i=1;i<=n;i++) pai[i] = i;
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		u = find(u);
		v = find(v);
		if(u != v){
			join(u,v);
			resposta[++vertice] = i;
			conjuntos--;
		}
	}
	if(conjuntos != 1){
		printf("Disconnected Graph\n");
		return 0;
	}
	for(int i=1;i<n;i++) printf("%d\n",resposta[i]);
	return 0;
}