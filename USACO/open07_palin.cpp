#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
char str[2005];
int cost[256];
int dp[2005][2005];

int f(int s, int e){
	if(s == 0 && e == n) return 0;
	if(~dp[s][e]) return dp[s][e];
	int ret = 1e9;
	if(s) ret = min(ret, f(s-1, e) + cost[str[s-1]]);
	if(e<n) ret = min(ret, f(s, e+1) + cost[str[e]]);
	if(s && e<n && str[s-1] == str[e]) ret = min(ret, f(s-1, e+1));
	return dp[s][e] = ret;
}

int main(){
	memset(dp,-1,sizeof(dp));
	int q;
	scanf("%d %d %s",&q,&n,str);
	while(q--){
		char t[5];
		int a, b;
		scanf("%s %d %d",t, &a, &b);
		cost[*t] = min(a, b);
	}
	int ret = 1e9;
	for(int i=0; i<n; i++){
		ret = min(ret, f(i+1, i));
		ret = min(ret, f(i, i));
	}
	printf("%d",ret);
}