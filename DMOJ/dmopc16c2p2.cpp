// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc16c2p2
#include <cstdio>
#define MAXN 100010
int pai[MAXN],peso[MAXN],conjuntos,vetor[MAXN];
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	conjuntos--;
	if(peso[x] < peso[y]){
		pai[x] = y;
	}
	else if(peso[x] > peso[y]){
		pai[y] = x;
	}
	else{
		pai[x] = y;
		peso[y]++;
	}
}
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		pai[i] = i;
	}
	conjuntos = n;
	while(m--){
		if(conjuntos == 1) break;
		int k;
		scanf("%d",&k);
		for(int i=1;i<=k;i++) scanf("%d",&vetor[i]);
		for(int i=2;i<=k;i++) join(vetor[i-1],vetor[i]);
	}
	int resp = 0;
	for(int i=1;i<=n;i++) resp += find(i) == find(1);
	printf("%d\n",resp);
	for(int i=1;i<=n;i++){
		if(find(i) == find(1)) printf("%d ",i);
	}
	printf("\n");
	return 0;
}