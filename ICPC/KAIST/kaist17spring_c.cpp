#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 9;

int n;
lint dp[1005][5]; 

int main(){
	cin >> n;
	dp[0][0] = 1;
	for(int i=1; i<=n; i++){
		dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2] + dp[i-1][4];
		dp[i][1] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
		dp[i][2] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2] + dp[i-1][3];
		dp[i][3] = dp[i-1][3] + dp[i-1][0];
		dp[i][4] = dp[i-1][4] + dp[i-1][2];
		for(int j=0; j<5; j++) dp[i][j] %= mod;
	}
	cout << dp[n][2];
}
