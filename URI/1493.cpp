// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1493
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define MAXN 1001
vector<int> grafo[MAXN],transposto[MAXN];
int dp[MAXN][MAXN],nivel[MAXN],n,m;
int solve(int x,int y){
	if(dp[x][y] != -1) return dp[x][y];
	if(nivel[x] < nivel[y]) swap(x,y);
	for(int i=0;i<transposto[x].size();i++){
		int v = transposto[x][i];
		if(solve(v,y)){
			return dp[x][y] = 1;
		}
	}
	return dp[x][y] = 0;
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		for(int i=1;i<=n;i++){
			nivel[i] = 0;
			grafo[i].clear();
			transposto[i].clear();
			for(int j=1;j<=n;j++){
				dp[i][j] = -1;
			}
		}
		for(int i=1;i<=n;i++){
			dp[1][i] = dp[i][1] = 1;
		}
		for(int i=1;i<=n;i++){
			dp[i][i] = 0;
		}
		while(m--){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			transposto[v].push_back(u);
		}
		queue<int> bfs;
		nivel[1] = 1;
		bfs.push(1);
		while(!bfs.empty()){
			int davez = bfs.front();
			bfs.pop();
			for(int i=0;i<grafo[davez].size();i++){
				int proximo = grafo[davez][i];
				if(nivel[proximo] == 0){
					nivel[proximo] = nivel[davez] + 1;
					bfs.push(proximo);
				}
			}
		}
		int resp = 0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				resp += solve(i,j);
			}
		}
		printf("%d\n",resp/2);
	}
	return 0;
}
