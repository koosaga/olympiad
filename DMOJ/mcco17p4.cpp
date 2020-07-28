// Ivan Carvalho
// Solution to https://dmoj.ca/problem/mcco17p4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2*1e5 + 10;
vector<int> grafo[MAXN];
int tipo[MAXN],grau[MAXN],n,m;
int topoSort(){
	queue<int> bfs[2];
	int contador = 0;
	for(int i=0;i<n;i++){
		for(int j : grafo[i]) grau[j]++;
	}
	for(int i=0;i<n;i++) if(grau[i] == 0) bfs[tipo[i]].push(i);
	int atual = 0;
	while(!bfs[0].empty() || !bfs[1].empty()){
		while(!bfs[atual].empty()){
			int v = bfs[atual].front();
			bfs[atual].pop();
			for(int u : grafo[v]){
				grau[u]--;
				if(grau[u] == 0) bfs[tipo[u]].push(u); 
			}
		}
		if(!bfs[atual ^ 1].empty()) contador++;
		atual ^= 1;
	}
	return contador;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++) scanf("%d",&tipo[i]);  
	while(m--){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
	}
	int resp = topoSort();
	for(int i=0;i<n;i++) tipo[i] ^= 1;
	resp = min(resp, topoSort() );
	printf("%d\n",resp);
	return 0;
}