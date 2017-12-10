#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1005;

int mx[MAXN][MAXN];
int n, k, a[MAXN];
int dp[MAXN][MAXN], ret[MAXN][MAXN], opt[MAXN][MAXN];

void solve(){
	memset(ret, 0x3f, sizeof(ret));
	for(int i=1; i<=n; i++){
		opt[i][i] = i;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j+i<=n; j++){
			for(int k=opt[j][i+j-1]; k<=opt[j+1][i+j]; k++){
				int cur = dp[j][k] + dp[k+1][i+j] + abs(a[k] - a[i+j]);
				if(ret[j][i+j] > cur){
					ret[j][i+j] = cur;
					opt[j][i+j] = k;
				}
			}
		//	printf("%d %d %d\n", j, i+j, ret[j][i+j]);
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=i; j<=n; j++) dp[i][j] = min(dp[i][j], ret[i][j]);
	}
}

int main(){
	cin >> n >> k;
	for(int i=1; i<=n; i++) cin >> a[i];
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++){
		int mxv = -1;
		for(int j=i; j<=n; j++){
			mxv = max(mxv, a[j]);
			mx[i][j] = mxv;
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	for(int i=1; i<=n; i++) dp[i][i] = 0;
	int ans = 1e9;
	for(int i=1; i<=k; i++) solve();
	cout << dp[1][n];
}
