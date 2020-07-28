// Ivan Carvalho
// Solution to https://www.spoj.com/problems/LKS/
#include <cstdio>
#include <algorithm>
using namespace std;
int dp[2000001];
int main(){
	int W,N;
	scanf("%d %d",&W,&N);
	while(N--){
		int v,w;
		scanf("%d %d",&v,&w);
		for(int i = W;i >= w;i--) dp[i] = max(dp[i], dp[i - w] + v);
	}
	int b = 0;
	while(W--) b = max(b,dp[W]);
	printf("%d\n",b);
	return 0;
}