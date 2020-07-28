// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PT07Y/
#include <bits/stdc++.h>
using namespace std;
int pai[10010],peso[10010],conjuntos;
int find(int x){
	while(x != pai[x]) x = pai[x];
	return x;
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	conjuntos--;
	if(peso[x] < peso[y]) pai[x] = y;
	else if(peso[x] > peso[y]) pai[y] = x;
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
		int a,b;
		scanf("%d %d",&a,&b);
		if(find(a) == find(b)){
			printf("NO\n");
			return 0;
		}
		else join(a,b);
	}
	if(conjuntos == 1) printf("YES\n");
	else printf("NO\n");
	return 0;
}