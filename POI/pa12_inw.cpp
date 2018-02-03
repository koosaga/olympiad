#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
typedef long long lint;

int n, a[MAXN];
lint dp[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		dp[i] = max(dp[i-1], (i >= 2 ? dp[i-2] : 0) + a[i]);
	}
	cout << dp[n] << endl;
}
