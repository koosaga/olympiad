#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
typedef long long lint;

int n, a[MAXN], b[MAXN], g[MAXN], f[MAXN];

int dp[1005], nxt[1005];

int main(){
	g[0] = 1;
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		f[i] = g[i-1] + 1;
		for(int j=1; j<=i; j++){
			g[i] = max(g[i], f[j] * g[i-j]);
		}
		cout << f[i] << endl;
	}
	return 0;
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++) scanf("%d",&b[i]);
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for(int i=1; i<=n; i++){
		nxt[0] = 1e9;
		for(int j=1; j<1005; j++) nxt[j] = dp[j-1];
		for(int j=0; j<1005; j++){
			if(dp[j] + 1 <= n && b[dp[j] + 1] != a[i]){
				nxt[j] = min(nxt[j], dp[j] + 1);
			}
			else nxt[j] = min(nxt[j], dp[j] + 2);
		}
		memcpy(dp, nxt, sizeof(dp));
	}
	for(int i=0; i<1005; i++){
		if(dp[i] <= n){
			cout << n + i << endl;
			return 0;
		}
	}
}
