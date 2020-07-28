// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1513
#include <cstdio>
#include <queue>
#include <algorithm>
#define MAXN 101
#define MAXK 16
#define MAXL 65636
#define MP make_pair
#define LIMIT 100000
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
int conversao[MAXN][MAXN],n,m,k,dist[MAXN][MAXN],processado[MAXN][MAXN],dp[MAXK][MAXL];
char entrada[MAXN][MAXN];
void bfs(int v, int x, int y){
	for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				processado[i][j] = 0;
			}
		}
	queue<iii> fila;
	fila.push(MP(0,MP(x,y)));
	while(!fila.empty()){
		iii davez = fila.front();
		fila.pop();
		int percorrido = davez.first, cordx = davez.second.first, cordy = davez.second.second;
		if (cordx < 0 || cordy < 0 || cordx > n || cordy > m || entrada[cordx][cordy] == '#') continue;
		if (processado[cordx][cordy]) continue;
		processado[cordx][cordy] = 1;
		if (conversao[cordx][cordy] != -1){
			dist[v][conversao[cordx][cordy]] = percorrido;
		}
		fila.push(MP(percorrido+1,MP(cordx+1,cordy+2)));
		fila.push(MP(percorrido+1,MP(cordx+1,cordy-2)));
		fila.push(MP(percorrido+1,MP(cordx-1,cordy+2)));
		fila.push(MP(percorrido+1,MP(cordx-1,cordy-2)));
		fila.push(MP(percorrido+1,MP(cordx+2,cordy+1)));
		fila.push(MP(percorrido+1,MP(cordx+2,cordy-1)));
		fila.push(MP(percorrido+1,MP(cordx-2,cordy+1)));
		fila.push(MP(percorrido+1,MP(cordx-2,cordy-1)));
	}
}
int tsp(int pos, int bitmask){
	if (dp[pos][bitmask] != -1) return dp[pos][bitmask];
	if (bitmask == (1 << (k+1)) - 1){
		return dp[pos][bitmask] = dist[pos][0];
	}
	int ans = LIMIT;
	for(int nxt = 0; nxt <= k; nxt++){
		if (nxt != pos && !(bitmask & (1 << nxt))){
			ans = min(ans,tsp(nxt,bitmask | (1 << nxt)) + dist[pos][nxt]);
		}
	}
	return dp[pos][bitmask] = ans;
}
int main(){
	while(scanf("%d %d %d",&n,&m,&k) && ( n || m || k)){
		for(int i=0;i<=k;i++){
			for(int j = 0; j <= (1 << (k+1)) - 1;j++){
				dp[i][j] = -1;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				conversao[i][j] = -1;
			}
		}
		for(int i=0;i<n;i++) scanf("%s",entrada[i]);
		int peoes = 0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if (entrada[i][j] == 'P'){
					conversao[i][j] = ++peoes;
				}
				if (entrada[i][j] == 'C'){
					conversao[i][j] = 0;
				}
			}
		}
		for(int i = 0;i<=k;i++){
			for(int j=0;j<=k;j++){
				dist[i][j] = LIMIT;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if (conversao[i][j] != -1) bfs(conversao[i][j],i,j);
			}
		}
		printf("%d\n",tsp(0,1));
	}
	return 0;
}
