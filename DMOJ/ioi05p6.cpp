// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi05p6
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
const int MAXN = 102;
const int MAXK = 52;
const int INF = 2*1e9;

vector<ii> grafo[MAXN];
int dp[MAXN][MAXN][MAXK],dist[MAXN][MAXN],qtd[MAXN],N,K;
bool vis1[MAXN][MAXN],vis2[MAXN][MAXN];

void dfs_dist(int v,int p,int depth){
	if(vis2[v][p]) return;
	vis2[v][p] = 1;
	dist[v][p] = depth;
	for(ii aresta : grafo[v]){
		dfs_dist(aresta.first,aresta.first,0);
		dfs_dist(aresta.first,p, depth + aresta.second);
	}
}

void solve(int v,int p){
	if(vis1[v][p]) return;
	vis1[v][p] = 1;
	int embutido = dist[v][p]*qtd[v];
	int knapsack[MAXK];
	for(int i = 0;i<=K;i++) knapsack[i] = embutido;
	for(ii aresta : grafo[v]){
		int u = aresta.first;
		solve(u,u);
		solve(u,p);
		int novo[MAXK];
		for(int i = 0;i<=K;i++){
			novo[i] = INF;
		}
		for(int peso = 0;peso<=K;peso++){
			for(int i = K;i>=peso;i--){
				novo[i] = min(novo[i], knapsack[i - peso] + dp[u][p][peso] );
				if(peso >= 1) novo[i] = min(novo[i], knapsack[i - peso] + dp[u][u][peso-1] );
			}
		}
		for(int i = 0;i<=K;i++) knapsack[i] = novo[i];
	}
	for(int i = 0;i<=K;i++) dp[v][p][i] = knapsack[i];
}

int main(){
	scanf("%d %d",&N,&K);
	for(int i = 1;i<=N;i++){
		int w,v,d;
		scanf("%d %d %d",&w,&v,&d);
		grafo[v].push_back(ii(i,d));
		qtd[i] = w;
	}
	dfs_dist(0,0,0);
	solve(0,0);
	printf("%d\n",dp[0][0][K]);
	return 0;
}
