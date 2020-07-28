// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c6p6
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1200;
int ancestor[MAXN],processado[MAXN],cap[MAXN][MAXN],qtd[MAXN],e1[MAXN],e2[MAXN],source,sink,special,n,m,total;
vector<int> grafo[MAXN],impares;
int bfs(){
	int bot = MAXN;
	memset(ancestor,-1,sizeof(ancestor));
	memset(processado,0,sizeof(processado));
	queue<int> bfs;
	bfs.push(source);
	while(!bfs.empty()){
		int v = bfs.front();
		bfs.pop();
		if(processado[v]) continue;
		processado[v] = 1;
		for(int u : grafo[v]){
			if(processado[u] || cap[v][u] <= 0) continue;
			ancestor[u] = v;
			bfs.push(u);
		}
	}
	if(!processado[sink]) return 0;
	for(int i = sink;i != source;i = ancestor[i]){
		bot = min(bot,cap[ancestor[i]][i]);
	}
	for(int i = sink;i != source;i = ancestor[i]){
		cap[ancestor[i]][i] -= bot;
		cap[i][ancestor[i]] += bot;
	}
	return bot;
}
int Edmond(){
	int flow = 0;
	while(true){
		int davez = bfs();
		if(davez == 0) break;
		flow += davez;
	}
	return flow;
}
int main(){
	scanf("%d %d",&n,&m);
	source = 0;special = n + m + 1;sink = n + m + 2;
	for(int i = 1;i<=n;i++){
		grafo[sink].push_back(i);grafo[i].push_back(sink);
		scanf("%d",&qtd[i]);
		total += qtd[i];
		cap[i][sink] = qtd[i];
		grafo[special].push_back(i);grafo[i].push_back(special);
		cap[special][i] = MAXN;
	}
	grafo[source].push_back(special);grafo[special].push_back(source);
	cap[source][special] = total - 2*m;
	for(int i = n + 1;i <= n+m;i++){
		scanf("%d %d",&e1[i],&e2[i]);
		grafo[source].push_back(i);grafo[i].push_back(source);
		cap[source][i] = 2;
		grafo[e1[i]].push_back(i);grafo[i].push_back(e1[i]);
		grafo[e2[i]].push_back(i);grafo[i].push_back(e2[i]);
		cap[i][e1[i]] = 2;
		cap[i][e2[i]] = 2;
	}
	printf("%d\n",Edmond()/2);
	for(int i = n + 1;i<=n+m;i++){
		int v1 = 2 - cap[i][e1[i]];
		int v2 = 2 - cap[i][e2[i]];
		printf("%d %d %d\n",e1[i],e2[i],v1);
		qtd[e1[i]] -= v1;
		qtd[e2[i]] -= v2;
	}
	for(int i = 1;i<=n;i++) if(qtd[i] % 2 == 1) impares.push_back(i);
	while(!impares.empty()){
		int v = impares.back();impares.pop_back();
		int u = impares.back();impares.pop_back();
		printf("%d %d 1\n",u,v);
	}
	while(qtd[1] >= 2){
			printf("1 2 2\n");
			qtd[1] -= 2;
		}
	for(int i = 2;i<=n;i++){
		while(qtd[i] >= 2){
			printf("%d 1 2\n",i);
			qtd[i] -= 2;
		}
	}
	return 0;
}	}
	}
	return 0;
}