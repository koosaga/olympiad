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
typedef pair<pi, pi> line;

int dp[1005];
int n, m;

int main(){
	scanf("%d %d",&n,&m);
	fill(dp, dp+m+1, -1e9);
	dp[1] = 0;
	for(int i=0; i<n; i++){
		int s[1005] = {}, ndp[1005];
		for(int j=1; j<=m; j++){
			scanf("%d",&s[j]);
			s[j] += s[j-1];
		}
		int minv = -1e9;
		for(int j=1; j<=m; j++){
			minv = max(minv, dp[j] - s[j-1]);
			ndp[j] = minv + s[j];
		}
		minv = -1e9;
		for(int j=m; j; j--){
			minv = max(minv, dp[j] + s[j]);
			ndp[j] = max(ndp[j], minv - s[j-1]);
		}
		for(int j=1; j<=m; j++){
			dp[j] = ndp[j];
		}
	}
	printf("%d",dp[m]);
}