// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg17s2
#include <cstdio>
#define MAXN 100010
int pai[MAXN],peso[MAXN],n,m;
int find(int x){
	while(x!=pai[x]) x = pai[x];
	return pai[x];
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x==y) return;
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
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) pai[i] = i;
	while(m--){
		char op;
		int u,v;
		scanf(" %c %d %d",&op,&u,&v);
		if(op == 'Q') printf("%c\n",(find(u) == find(v)) ? 'Y' : 'N');
		else join(u,v);
	}
	return 0;
}