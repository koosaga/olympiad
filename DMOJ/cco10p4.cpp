// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco10p4
#include <cstdio>
#include <algorithm>
#define MAXN 3001
#define MAXL 32
using namespace std;
int dp[MAXN][MAXL];
int main(){
	int T,B,N;
	scanf("%d %d",&T,&N);
	int resp = 0;
	while(N--){
		int c,v,t;
		scanf("%d %d %d",&c,&v,&t);
		t--;
		for(int bitmask = 0;bitmask < (1 << T);bitmask++){
			if(bitmask & (1 << t)) continue;
			for(int j = 0;j + c < MAXN;j++){
				dp[j+c][bitmask | (1 << t)] = max(dp[j+c][bitmask | (1 << t)] , dp[j][bitmask] + v);
			}
		}
	}
	scanf("%d",&B);
	int bitmask = (1 << T) - 1;
	for(int i = B;i>=0;i--){
		resp = max(resp,dp[B][bitmask]);
	}
	if(resp == 0) resp = -1;
	printf("%d\n",resp);
	return 0;
}