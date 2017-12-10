#include <cstdio>
#include <cstring>

int dp[22][22][156];
int f(int k, int l, int s){
	if(k == 0) return (s == 0);
	if(s == 0) return 0;
	if(~dp[k][l][s]) return dp[k][l][s];
	int ret = 0;
	for(int i=1; i<=l && i<=s; i++){
		ret += f(k-1,i-1,s-i);
	}
	return dp[k][l][s] = ret;
}
bool solve(){
	int a, b, c;
	scanf("%d %d %d",&a,&b,&c);
	if(a + b + c == 0) return 0;
	printf("%d\n",f(b, a, c));
	return 1;
}

int main(){
	memset(dp,-1,sizeof(dp));
	while(solve());
}