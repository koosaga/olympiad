// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpb
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
const int INF = 2*1e9;

int dp[MAXN],N,K,h[MAXN];

int main(){

	scanf("%d %d",&N,&K);
	for(int i = 1;i<=N;i++){
		scanf("%d",&h[i]);
	}

	for(int i = 2;i<=N;i++){
		dp[i] = INF;
		for(int j = i-1;j>=max(i - K,1);j--){
			dp[i] = min(dp[i], dp[j] + abs(h[i] - h[j]) );
		}
	}

	printf("%d\n",dp[N]);

	return 0;

}