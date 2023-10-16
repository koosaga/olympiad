#include <bits/stdc++.h>
using namespace std;
const int MAXN = 128;

int dp[MAXN];

int main(){
	for(int i=2; i<128; i++){
		bool vis[MAXN] = {};
		for(int j=0; j<=i-2; j++) vis[dp[j] ^ dp[i - j - 2]] = 1;
		while(vis[dp[i]]) dp[i]++;
	}
	int tc; scanf("%d",&tc);
	while(tc--){
		long long n; scanf("%lld",&n);
		if(n >= MAXN){ // dp[i] = dp[i - 34] for i >= 86
			n -= ((n - MAXN) / 34) * 34;
			n -= 34;
		}
		if(dp[n])puts("First");
		else puts("Second");
	}
}