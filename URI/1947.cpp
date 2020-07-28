// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1947
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#define MP make_pair
#define PB push_back
using namespace std;
typedef pair<int,int> ii;
const int MAXK = 17;
const int MAXN = 1e4 + 10;
const int MAXL = (1 << 16) + 100;
int dp[MAXK][MAXL],ini[MAXK],fim[MAXK],custo[MAXK][MAXK],N,M,K,processado[MAXN];
vector<ii> grafo[MAXN];
map<ii,int> precalculo;
int Dijkstra(int S,int T){
	if(precalculo.count(MP(S,T))) return precalculo[MP(S,T)];
	for(int i=1;i <= N;i++){
		processado[i] = 0;
	}
	priority_queue<ii, vector<ii>, greater<ii> >  SSSP;
	SSSP.push(MP(0,S));
	while(!SSSP.empty()){
		ii davez = SSSP.top();
		SSSP.pop();
		int v = davez.second, percorrido = davez.first;
		if(processado[v]) continue;
		processado[v] = 1;
		precalculo[MP(S,v)] = percorrido;
		for(ii proximo : grafo[v]){
			SSSP.push(MP(percorrido + proximo.second,proximo.first));
		}
	}
	return precalculo[MP(S,T)];
}
int solve(int pos,int bitmask){
	if(dp[pos][bitmask] != -1) return dp[pos][bitmask];
	if(bitmask == (1 << K) - 1){
		return dp[pos][bitmask] = custo[pos][0];
	}
	int melhor = 1e8;
	for(int prox = 0;prox < K;prox++){
		if(pos != prox && !(bitmask & (1 << prox))){
			melhor = min(melhor, custo[pos][prox] + solve(prox, bitmask | (1 << prox) ) );
		}
	}
	return dp[pos][bitmask] = melhor;
}
int main(){
	scanf("%d %d %d",&N,&M,&K);
	for(int i=1;i<=M;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		grafo[u].PB(MP(v,peso));
		grafo[v].PB(MP(u,peso));
	}
	int base = 0;
	for(int i=1;i<=K;i++){
		scanf("%d %d",&ini[i],&fim[i]);
		base += Dijkstra(ini[i],fim[i]);
	}
	K++;
	ini[0] = fim[0] = 1;
	for(int i=0;i<K;i++){
		for(int j=0;j<K;j++){
			custo[i][j] = Dijkstra(fim[i],ini[j]);
			//printf("Custo[%d][%d] = %d\n",i,j,custo[i][j]);
		}
	}
	for(int l=0;l<K;l++){
		for(int r=0;r<(1 << K);r++){
			dp[l][r] = -1;
		}
	}
	printf("%d\n",base + solve(0,1));
	return 0;
}
