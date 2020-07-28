// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco07p6
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;

typedef pair<int,int> ii;

vector<ii> arestas;
vector<int> tipo;
int pai[MAXN],grau[MAXN],n,r,pontes;

void reseta(){
	for(int i = 1;i<=n;i++) pai[i] = i;
}

int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}

void join(int x,int y){
	x = find(x);y = find(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	pai[y] = x;
}

int main(){
	scanf("%d %d",&n,&r);
	reseta();

	for(int i = 1;i<=r;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		arestas.push_back(ii(u,v));
	}

	for(int i = 0;i < r;i++){
		reseta();
		for(int j = 0;j < i;j++) join(arestas[j].first,arestas[j].second);
		for(int j = i+1;j < r;j++) join(arestas[j].first,arestas[j].second);
		if(find(arestas[i].first) != find(arestas[i].second)){
			tipo.push_back(1);
		}
		else{
			tipo.push_back(0);
		}
	}

	reseta();
	for(int i = 0;i<r;i++){
		if(tipo[i] == 0) join(arestas[i].first,arestas[i].second);
	}

	for(int i = 0;i<r;i++){
		if(tipo[i] == 1){
			grau[find(arestas[i].first)]++;
			grau[find(arestas[i].second)]++;
		}
	}

	int folhas = 0;

	for(int i = 1;i<=n;i++) if(find(i) == i && grau[i] == 1) folhas++;

	printf("%d\n",(folhas+1)/2);
	return 0;
}
