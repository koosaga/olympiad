#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int dp[105][10005];
int n, w, h;

int main(){
	dp[0][0] = 1;
	cin >> n >> w >> h;
	for(int i=1; i<=w; i++){
		for(int j=0; j<=n; j++){
			for(int k=0; k<=h && k<=j; k++){
				dp[i][j] += dp[i-1][j-k];
				dp[i][j] %= mod;
			}
		}
	}
	int ans = 0;
	for(int i=0; i<=n && i<=w*h; i++){
		ans += dp[w][i];
		ans %= mod;
		if(i % w == 0){
			ans += mod - 1;
			ans %= mod;
		}
	}
	cout << ans;
}
