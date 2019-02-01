#include <bits/stdc++.h>
typedef long long lint;
typedef long double llf;
using namespace std;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, m, k, a[1005];
int dp[1005][105];

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<n; i++){
		int x;
		cin >> x;
		a[i] += x;
	}
	for(int i=0; i<n; i++){
		int x;
		cin >> x;
		a[i] += k - x;
		a[i] %= k;
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<k; j++){
			if(j == a[n-1]) dp[i][j] = i <= 1 ? 0 : 1e9;
			else dp[i][j] = i <= 0 ? 0 : 1e9;
		}
	}
	for(int i=n-2; i>=0; i--){
		for(int j=n; j; j--){
			int ret = 1e9;
			for(int l=0; l<k; l++){
				ret = min(ret, dp[j][l] + min(l, k-l));
			}
			for(int l=0; l<k; l++){
				int p = (a[i] - l + k) % k;
				dp[j][l] = min(ret, dp[j-1][p] + min(p, k-p));
			}
		}
	}
	for(int i=n; i>=0; i--){
		if(dp[i][0] <= m/2){
			cout << n-i << endl;
			return 0;
		}
	}
}
