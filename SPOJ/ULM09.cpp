// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ULM09/
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 200100
int pai[MAXN],peso[MAXN],n,m;
pair<int, pair<int,int> > vetor[MAXN];
int find(int x){
	if (x==pai[x]) return x;
	return pai[x]=find(pai[x]);
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if (peso[x]<peso[y]) pai[x]=y;
	else if (peso[x]>peso[y]) pai[y]=x;
	else {
		pai[x]=y;
		peso[y]++;
	}
}
int main(){
	while(1){
		int total = 0;
		scanf("%d %d",&n,&m);
		if (n==0 && m == 0) break;
		for(int i=0;i<n;i++) {pai[i]=i;peso[i]=0;}
		for(int i=0;i<m;i++){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			total += peso;
			vetor[i]=make_pair(peso,make_pair(u,v));
		}
		sort(vetor,vetor+m);
		for(int i=0;i<m;i++) if (find(vetor[i].second.first)!=find(vetor[i].second.second)){
			total -= vetor[i].first;
			join(vetor[i].second.first,vetor[i].second.second);
		}
		printf("%d\n",total);
	}
	return 0;
}