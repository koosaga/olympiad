// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep16c2q2
#include <cstdio>
#include <algorithm>
#define MAXL 31
using namespace std;
int dp[MAXL];
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		int davez;
		scanf("%d",&davez);
		int best = 0;
		for(int i=0;i<MAXL;i++){
			if(davez & (1 << i)){
				best = max(dp[i] + 1,best);
			}
		}
		for(int i=0;i<MAXL;i++){
			if(davez & (1 << i)){
				dp[i] = max(dp[i],best);
			}
		}
	}
	int resp = 0;
	for(int i=0;i<MAXL;i++) resp = max(resp,dp[i]);
	printf("%d\n",resp);
	return 0;
}