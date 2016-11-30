#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, lint> pi;

int n, k, cnt0[1000005], cnt1[1000005], dp[1000005][2];

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		int t;
		scanf("%d",&t);
		if(t % 2 == 0) cnt0[i%k+1]++;
		else cnt1[i%k+1]++;
	}
	dp[0][1] = 1e9;
	for(int i=1; i<=k; i++){
		dp[i][0] = min(dp[i-1][1] + cnt0[i], dp[i-1][0] + cnt1[i]);
		dp[i][1] = min(dp[i-1][0] + cnt0[i], dp[i-1][1] + cnt1[i]);
	}
	cout << dp[k][0];
}