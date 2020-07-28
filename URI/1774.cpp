// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1774
#include <algorithm>
#include <cstdio>
#define MAX 300
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
iii grafo[MAX];
int pai[MAX],peso[MAX];
int find(int x){
	if (x==pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if (x==y) return;
	if (peso[x]==peso[y]){
		pai[x] = y;
		peso[y]++;
	}
	if (peso[x]>peso[y]) pai[y] = x;
	else pai[x] = y;
}
int main(){
	int n,m,resposta=0;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) pai[i]=i;
	for(int i=0;i<m;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		grafo[i] = MP(peso,MP(u,v));
	}
	sort(grafo,grafo+m);
	for(int i=0;i<m;i++) if (find(grafo[i].second.first)!=find(grafo[i].second.second)) {
		resposta += grafo[i].first;
		join(grafo[i].second.first,grafo[i].second.second);
	}
	printf("%d\n",resposta);
	return 0;
}
