#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m, a[1005], b[1005];
int dp[1005][1005];

int f(int x, int y){
	if(x == 0 && y == 0) return 0;
	if(~dp[x][y]) return dp[x][y];
	int ret = 2e9;
	if(x > 0) ret = min(ret, f(x-1, y) + a[x-1] * (m+1-y));
	if(y > 0) ret = min(ret, f(x, y-1) + b[y-1] * (n+1-x));
	return dp[x][y] = ret;
}

int main(){
	memset(dp, -1, sizeof(dp));
	cin >> n >> m;
	n--, m--;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<m; i++) cin >> b[i];
	sort(a, a+n);
	sort(b, b+m);
	cout << f(n, m);
}
