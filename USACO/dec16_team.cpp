#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 9;

int n, m, k, a[1005], b[1005];
lint dp[11][1005][1005];

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<m; i++) cin >> b[i];
	sort(a, a+n);
	reverse(a, a+n);
	sort(b, b+m);
	reverse(b, b+m);
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			dp[0][i][j] = 1;
		}
	}
	lint ret = 0;
	for(int i=1; i<=k; i++){
		for(int j=n-1; j>=0; j--){
			for(int l=m-1; l>=0; l--){
				if(a[j] > b[l]){
					dp[i][j][l] = dp[i-1][j+1][l+1];
					if(i == k) ret += dp[i][j][l];
				}
				dp[i][j][l] += dp[i][j+1][l] + dp[i][j][l+1] - dp[i][j+1][l+1] + mod;
				dp[i][j][l] %= mod;
			}
		}
	}
	ret %= mod;
	cout << ret;
}
