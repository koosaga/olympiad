#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, q;
int nxt[10000005];
int dp[10000005];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		for(int j=x; j-1<=10000000; j+=x){
			nxt[j-1] = x-1;
		}
		nxt[10000000] = max(nxt[10000000], 10000000 % x);
	}
	for(int i=10000000; i; i--) nxt[i] = max(nxt[i], nxt[i+1] - 1);
	for(int i=1; i<=10000000; i++){
		if(dp[i - nxt[i]] == -1 || nxt[i] == 0) dp[i] = -1;
		else dp[i] = dp[i - nxt[i]] + 1;
	}
	while(q--){
		int x;
		scanf("%d",&x);
		if(dp[x] < 0) puts("oo");
		else printf("%d\n", dp[x]);
	}
}
