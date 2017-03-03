#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k;
int a[1000005], dp[1000005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	dp[0] = a[0];
	dp[1] = a[1];
	for(int i=2; i<n; i++){
		dp[i] = min(dp[i-2] + a[i] + a[0] + a[1] + a[1], dp[i-1] + a[i] + a[0]);
	}
	printf("%d", dp[n-1]);
}
