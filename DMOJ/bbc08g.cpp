// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bbc08g
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef tuple<int,int,int,int,int,int> sextupla;

const int MAXN = 1e5 + 10;
const int INF = 1e9; 

vector<ii> grafo[MAXN];
vector<int> resposta,numeral;
int liga[MAXN],processado[2][MAXN],meurank,N,M,pai[2][MAXN];

void BFS(){

	for(int i = 0;i<N;i++){
		processado[0][i] = INF;
		pai[0][i] = -1;
	}

	queue<ii> bfs;
	bfs.push(ii(0,N-1));
	processado[0][N-1] = 0;

	while(!bfs.empty()){
		ii davez = bfs.front();
		bfs.pop();
		int v = davez.second, dist = davez.first;
		for(ii aresta : grafo[v]){
			int u = aresta.first, w = aresta.second;
			if(w != 0) continue;
			if(processado[0][u] != INF) continue;
			processado[0][u] = dist + 1;
			pai[0][u] = v;
			bfs.push(ii(dist+1,u));
		}
	}

}

int Dijkstra(){		

	for(int i = 0;i<N;i++){
		liga[i] = -1;
		pai[1][i] = -1;
	}

	priority_queue<sextupla, vector<sextupla>, greater<sextupla> > 
pq;
	pq.push(make_tuple(0,-1,0,processado[0][0],-1,0));

	while(!pq.empty()){
		sextupla davez = pq.top();
		pq.pop();
		int dist = get<0>(davez);
		int digit = get<1>(davez);
		//int p_rank = get<2>(davez);
		int d_z = get<3>(davez);
		int parent = get<4>(davez);
		int v = get<5>(davez);
		if(processado[1][v]) continue;
		processado[1][v] = ++meurank;
		liga[v] = digit;
		pai[1][v] = parent;
		if(d_z != INF) return v;
		for(ii aresta : grafo[v]){
			int u = aresta.first, w = aresta.second;
			if(processado[1][u]) continue;
			
pq.push(make_tuple(dist+1,w,processado[1][v],processado[0][u],v,u));
		}
	}

	return -1;

}

int main(){

	scanf("%d %d",&N,&M);
	for(int i = 1;i<=M;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		grafo[u].push_back(ii(v,w));
		grafo[v].push_back(ii(u,w));
	}
	
	BFS();
	int meio = Dijkstra();
	int atual = meio;
	
	while(pai[1][atual] != -1){
		resposta.push_back(atual);
		numeral.push_back(liga[atual]);
		atual = pai[1][atual];
	}
	resposta.push_back(0);

	reverse(resposta.begin(),resposta.end());

	atual = pai[0][meio];
	while(atual != -1){
		resposta.push_back(atual);
		atual = pai[0][atual];
	}

	if(numeral.empty()) numeral.push_back(0);
	for(int i : numeral){
		printf("%d",i);
	}
	printf("\n");
	printf("%d\n",(int)resposta.size());
	for(int i = 0;i<(int)resposta.size();i++){
		if(i) printf(" ");
		printf("%d",resposta[i]);
	}
	printf("\n");

	return 0;

}
