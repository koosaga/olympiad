// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc07s4
#include <cstdio>
#include <vector>
#include <cstring>
#define MAXN 10000
using namespace std;
vector<int> grafo[MAXN];
int dp[MAXN],n;
int func(int atual){
	if (dp[atual] != -1) return dp[atual];
	int val = 0;
	for(int i=0;i<int(grafo[atual].size());i++) val += func(grafo[atual][i]);
	return dp[atual] = val;
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	dp[n] = 1;
	int origem,destino;
	while(true){
		scanf("%d %d",&origem,&destino);
		if (origem == 0 && destino == 0) break;
		grafo[origem].push_back(destino);
	}
	printf("%d\n",func(1));
	return 0;
}