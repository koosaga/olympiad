// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1323
#include <cstdio>
int dp[110];
int main(){
	int n;
	for(int i=1;i<=100;i++){
		dp[i] = dp[i-1] + i*i;
	}
	while(scanf("%d",&n) && n){
		printf("%d\n",dp[n]);
	}
	return 0;
}
