// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ncco4d1p3
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

const int MAXN = 5*1e3 + 10;
const int INF = 1e9;

vector<ii> grafo[MAXN];
int processado[MAXN][2],dist[MAXN][2],N,M;

int main(){
	
	scanf("%d %d",&N,&M);
	for(int i = 1;i<=M;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		grafo[u].push_back(ii(v,w));
		grafo[v].push_back(ii(u,w));
	}

	for(int i = 1;i<=N;i++){
		dist[i][0] = dist[i][1] = INF;
	}

	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0,1));

	while(!pq.empty()){
		int v = pq.top().second, percorrido = pq.top().first;
		pq.pop();
		if(processado[v][0]){
			if(percorrido == dist[v][0]) continue;
			if(processado[v][1]) continue;
			processado[v][1] = 1;
			dist[v][1] = percorrido;
		}
		else{
			processado[v][0] = 1;
			dist[v][0] = percorrido;
		}
		for(ii e : grafo[v]){
			int u = e.first, w = e.second;
			pq.push(ii(w+percorrido,u));
		}
	}

	printf("%d\n",dist[N][1]);

	return 0;

}
