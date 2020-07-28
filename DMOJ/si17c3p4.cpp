// Ivan Carvalho
// Solution to https://dmoj.ca/problem/si17c3p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2*1e4 + 10;
const int MOD = 1e9 + 7;

vector<int> grafo[MAXN];
int num[MAXN],low[MAXN],dfsParent[MAXN],level[MAXN],dfsCount,went_up[MAXN],isCactus,N,M;
ll ans;

void dfs(int v,int p){

	if(!isCactus) return;

	num[v] = ++dfsCount;
	low[v] = num[v];

	for(int u : grafo[v]){
		if(u == p) continue;
		if(num[u] == 0){
			dfsParent[u] = v;
			level[u] = level[v] + 1;
			dfs(u,v);
		}
		else if(num[u] < num[v]){
			low[v] = min(low[v],num[u]);
			ans = (ans * (level[v] - level[u] + 1)) % MOD;
			int k = v;
			while(k != u){
				if(went_up[k]){
					isCactus = 0;
					break;
				}
				went_up[k] = 1;
				k = dfsParent[k];
			}
		}
	}

}

int main(){

	ans = 1;
	isCactus = 1;
	scanf("%d %d",&N,&M);
	for(int i = 1;i<=M;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1,-1);

	for(int i = 2;i<=N;i++){
		if(num[i] == 0) isCactus = 0;
	}

	if(isCactus) printf("%lld\n",ans);
	else printf("safe\n");

	return 0;
}