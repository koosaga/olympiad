// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1764
#include <cstdio>
#include <algorithm>
#define MAXN 40100
#define MAXM 50100
using namespace std;
int pai[MAXN],peso[MAXN],n,m;
pair<int, pair<int,int> > vetor[MAXM];
int find(int x){
	if (x==pai[x]) return x;
	return pai[x]=find(pai[x]);
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if (x==y) return;
	if (peso[x]<peso[y]) pai[x]=y;
	else if (peso[x]>peso[y]) pai[y]=x;
	else{
		pai[x]=y;
		peso[y]++;
	}
}
int main(){
	while(1){
		scanf("%d %d",&n,&m);
		if (n==0 && m==0) break;
		int resposta = 0;
		for(int i=0;i<n;i++) {pai[i]=i;peso[i]=0;}
		for(int i=0;i<m;i++){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			vetor[i]=make_pair(peso,make_pair(u,v));
		}
		sort(vetor,vetor+m);
		for(int i=0;i<m;i++) if (find(vetor[i].second.first)!=find(vetor[i].second.second)){
			resposta += vetor[i].first;
			join(vetor[i].second.first,vetor[i].second.second);
		}
		printf("%d\n",resposta);
	}
	return 0;
}
