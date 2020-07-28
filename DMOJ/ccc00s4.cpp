// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc00s4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5290;
int dp[MAXN],n,k;
int main(){
	scanf("%d %d",&k,&n);
	for(int i = 0;i<=k;i++){
		dp[i] = MAXN;
	}
	dp[0] = 0;
	while(n--){
		int x;
		scanf("%d",&x);
		for(int i = x;i<=k;i++){
			dp[i] = min(dp[i - x] + 1,dp[i]);
		}
	}
	if(dp[k] == MAXN) printf("Roberta acknowledges defeat.\n");
	else printf("Roberta wins in %d strokes.\n",dp[k]);
	return 0;
}