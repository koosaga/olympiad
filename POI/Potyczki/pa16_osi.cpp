#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n,m;
int bino[1005][1005];
lint dp[505][505], nxt[505][505];

void make_psum(){
	for(int i=1; i<=m; i++){
		for(int j=1; j<=m; j++){
			dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
			dp[i][j] += mod;
			dp[i][j] %= mod;
		}
	}
}

int main(){
	cin >> n >> m;
	for(int i=0; i<=1001; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % mod;
		}
	}
	lint ret = 1;
	for(int i=1; i<=m; i++) dp[1][i] = 1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			for(int k=1; k<=j; k++){
				ret += (dp[k][j] * bino[n][i] % mod) * bino[m][j] % mod;
				ret %= mod;
			}
		}
		make_psum();
		memset(nxt, 0, sizeof(nxt));
		for(int j=1; j<=m; j++){
			for(int k=j; k<=m; k++){
				nxt[j][k] = dp[j][k] - (j - 2 >= 0 ? dp[j][j-2] : 0) + mod;
				nxt[j][k] %= mod;
			}
		}
		memcpy(dp, nxt, sizeof(dp));
	}
	cout << ret;
}
