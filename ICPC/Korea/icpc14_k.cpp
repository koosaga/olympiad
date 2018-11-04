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

int n, a[10005], b[10005];
int dp[10005][33];

int f(int x, int k){
	if(x >= n) return 0;
	if(~dp[x][k]) return dp[x][k];
	int ret = 1e9;
	ret = min(ret, f(x+1, max(k-1, 0)) + 6);
	ret = min(ret, f(x+7, max(k-7, 0)) + 36);
	ret = min(ret, f(x+30, max(k-30, 0)) + 90);
	if(k < 1) ret = min(ret, f(x, 1) + 3);
	if(k < 7) ret = min(ret, f(x, 7) + 18);
	if(k < 30) ret = min(ret, f(x, 30) + 45);
	if(k == 0) ret = min(ret, f(x+1, 0) + a[x] + 2 * b[x]);
	else ret = min(ret, f(x+1, k-1) + 2 * b[x]);
	return dp[x][k] = ret;
}
void solve(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i], &b[i]);
	}
	memset(dp, -1, sizeof(dp));
	cout << f(0, 0) << endl;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}