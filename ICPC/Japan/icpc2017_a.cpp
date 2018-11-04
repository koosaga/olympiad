#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 105;

int n, k;
lint dp[MAXN];

int main(){
	cin >> n >> k;
	for(int i=1; i<=n; i++){
		if(i >= 1) dp[i] += 1;
		if(i >= 2) dp[i] += dp[i-2];
		if(i >= k) dp[i] += 1;
		if(i >= k + 1) dp[i] += dp[i-k-1];
	}
	cout << dp[n] << endl;
}