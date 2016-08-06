#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
 
int dp[3005][3005];
int n, t, a[3005], b[3005], c[3005], d[3005];
 
int main(){
	memset(dp[0], 0x3f, sizeof(dp[0]));
	scanf("%d %d",&n,&t);
	for(int i=1; i<=n; i++){
		scanf("%d %d %d %d",&a[i], &b[i], &c[i], &d[i]);
	}
	dp[0][0] = t;
	for(int i=1; i<=n; i++){
		int pmin = 1e9;
		for(int j=0; j<=n; j++){
			dp[i][j] = dp[i-1][j] + t + a[i] + b[i] + 2 * j * t;
			if(j < n) dp[i][j] = min(dp[i][j], dp[i-1][j+1] + t + a[i] + d[i] + 2 * (j+1) * t);
			if(j) dp[i][j] = min(dp[i][j], dp[i-1][j] + t + c[i] + d[i] + 2 * j * t);
			dp[i][j] = min(dp[i][j], pmin + j * (b[i] + c[i]));
			pmin = min(pmin, dp[i-1][j] + t - j * (b[i] + c[i]) + 2 * j * t);
		}
	}
	printf("%d",dp[n][0]);
}