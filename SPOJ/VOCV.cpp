// Ivan Carvalho
// Solution to https://www.spoj.com/problems/VOCV/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
const int MOD = 10007;
vector<int> grafo[MAXN];
int dp[MAXN][2],calc[MAXN][2],n,TC;
int solve(int v,int p,int estado){
	if(dp[v][estado] != -1) return dp[v][estado];
	if(estado == 0){
		int ret = 0;
		for(int u : grafo[v]){
			if(u == p) continue;
			ret += 1 + solve(u,v,1);
		}
		return dp[v][estado] = ret;
	}
	else{
		int ret = 0;
		for(int u : grafo[v]){
			if(u == p) continue;
			ret += min(1 + solve(u,v,1), solve(u,v,0) );
		}
		return dp[v][estado] = ret;
	}
}
int count(int v,int p,int estado){
	if(calc[v][estado] != -1) return calc[v][estado];
	if(estado == 0){
		int ret = 1;
		for(int u : grafo[v]){
			if(u == p) continue;
			ret *= count(u,v,1);
			ret %= MOD;
		}
		return calc[v][estado] = ret;
	}
	else{
		int ret = 1;
		for(int u : grafo[v]){
			if(u == p) continue;
			if(1 + solve(u,v,1) < solve(u,v,0)){
				ret *= count(u,v,1);
				ret %= MOD;
			}
			else if(1 + solve(u,v,1) > solve(u,v,0)){
				ret *= count(u,v,0);
				ret %= MOD;
			}
			else{
				ret *= count(u,v,0) + count(u,v,1);
				ret %= MOD;
			}
		}
		return calc[v][estado] = ret;
	}
}
int main(){
	scanf("%d",&TC);
	for(int tc = 1;tc<=TC;tc++){
		scanf("%d",&n);
		for(int i = 1;i<=n;i++){
			dp[i][0] = dp[i][1] = calc[i][0] = calc[i][1] = -1;
			grafo[i].clear();
		}
		if(n == 1){
			printf("1 1\n");
			continue;
		}
		for(int i = 1;i<n;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		if(1 + solve(1,-1,1) < solve(1,-1,0)){
			printf("%d %d\n",1 + solve(1,-1,1),count(1,-1,1));
		}
		else if(1 + solve(1,-1,1) > solve(1,-1,0)){
			printf("%d %d\n",solve(1,-1,0),count(1,-1,0));
		}
		else{
			printf("%d %d\n",solve(1,-1,0),(count(1,-1,0) + count(1,-1,1)) % MOD);
		}
	}
	return 0;
}