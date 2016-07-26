#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

lint dp[2005][2005];
int n, s, t;

int main(){
	freopen("kangaroo.in", "r", stdin);
	freopen("kangaroo.out", "w", stdout);
	cin >> n >> s >> t;
	dp[n+1][1] = 1;
	int f = 2;
	for(int i=n; i; i--){
		for(int j=1; j<=n; j++){
			if(i == s || i == t){
				dp[i][j] = (dp[i+1][j] + dp[i+1][j+1]) % mod;
			}
			else{
				dp[i][j] = (dp[i+1][j-1] * (j-1) + dp[i+1][j+1] * (j + 1 - f)) % mod;
			}
		}
		if(i == s || i == t) f--;
	}
	cout << dp[2][1];
}

