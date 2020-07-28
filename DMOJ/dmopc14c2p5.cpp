// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c2p5
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
vector<int> grafo[MAXN];
double dp[MAXN];
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
	}
	dp[1] = 1.0;
	for(int i=1;i<=n;i++){
		if(grafo[i].size() == 0){
			printf("%.9lf\n",dp[i]);
			continue;
		}
		double qtd = (double)grafo[i].size();
		for(int j : grafo[i]) dp[j] += dp[i]/qtd;
	}
	return 0;
}