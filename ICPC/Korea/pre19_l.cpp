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

int t, n, a[1005], b[1005];

int dp[2][100005];

void solve(){
	memset(dp, 0x3f, sizeof(dp));
	dp[1][0] = 0;
	int s = 0;
	for(int i=0; i<n; i++){
		s += max(a[i], b[i]);
		for(int j=s; j>=0; j--){
			dp[i%2][j] = 1e9;
			if(j >= a[i]) dp[i%2][j] = min(dp[i%2][j], dp[(i+1)%2][j - a[i]]);
			dp[i%2][j] = min(dp[i%2][j], dp[(i+1)%2][j] + b[i]);
		}
	}
	int ret = 1e9;
	for(int i=0; i<=s; i++){
		ret = min(ret, max(i, dp[(n-1)%2][i]));
	}
	cout << ret << endl;
}

int main(){
    t = 1;
	for(int i=0; i<t; i++){
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			scanf("%d %d",&a[i],&b[i]);
		}
		solve();
	}
}