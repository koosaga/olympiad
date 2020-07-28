// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2014
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> vi;
const int MAXN = 1e3 + 1;
vi pilha[MAXN],vis,match,grafo[MAXN];
int N,Q;
int augmenting_path(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(int i=0;i<grafo[l].size();i++){
		int r = grafo[l][i];
		if(match[r] == -1 || augmenting_path(match[r])){
			match[r] = l;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d %d",&N,&Q);
	for(int pai=1;pai <= N;pai++){
		int qtd;
		scanf("%d",&qtd);
		if(qtd != N) pilha[0].push_back(pai);
		while(qtd--){
			int alelo;
			scanf("%d",&alelo);
			pilha[alelo].push_back(pai);
		}
	}
	while(Q--){
		for(int i=1;i<=N;i++){
			grafo[i].clear();
		}
		match.assign(N+1,-1);
		vi possiveis;
		int requer;
		scanf("%d",&requer);
		if(requer != N) possiveis = pilha[0];
		for(int i=1;i<=requer;i++){
			int j;
			scanf("%d",&j);
			for(int k=0;k<pilha[j].size();k++){
				grafo[i].push_back(pilha[j][k]);
				possiveis.push_back(pilha[j][k]);
			}
		}
		sort(possiveis.begin(),possiveis.end());
		unique(possiveis.begin(),possiveis.end());
		for(int i = requer+1;i<=N;i++){
			grafo[i] = possiveis;
		}
		int resp = 0;
		for(int i=1;i<=N;i++){
			vis.assign(N+1,0);
			resp += augmenting_path(i);
		}
		if(resp == N) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
