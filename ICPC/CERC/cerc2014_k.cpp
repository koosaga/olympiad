#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, k;
pi a[150005];
int dp[11][150005];
 
void solve(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	sort(a, a+n);
	int ret = 0;
	for(int i=n-1; i>=0; i--){
		dp[0][i] = max(dp[0][i+1], a[i].first - a[i].second);
	}
	for(int i=1; i<=k; i++){
		for(int j=n-1; j>=0; j--){
			dp[i][j] = max(dp[i][j+1], min(a[j].first - a[j].second, dp[i-1][j+1] - a[j].second));
		}
	}
	printf("%d\n",dp[k][0]);
	for(int i=0; i<=k; i++){
		memset(dp[i], 0, sizeof(int) * (n+5));
	}
}
 
int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}