// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c2p4
#include <cstdio>
int dp[1000010],n,q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&dp[i]);
		dp[i] += dp[i-1];
	}
	scanf("%d",&q);
	while(q--){
		int a,b;
		scanf("%d %d",&a,&b);
		a++;
		b++;
		printf("%d\n",dp[b] - dp[a-1]);
	}
	return 0;
}