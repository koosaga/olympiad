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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, s, a[1000005];
lint dp[1000005];

int main(){
	scanf("%d %d",&n,&s);
	a[0] = -1;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i] = max(a[i] - i, a[i-1]);
	}
	int p = 0;
	dp[0] = -1;
	for(int i=1; i<=n; i++){
		while(p < i && dp[p] < a[i]) p++; // dp[p] >= a[i], dp[p-1] < a[i]
		dp[i] = 1e18;
		if(p) dp[i] = min(dp[i],1ll * a[i] + 2 * (s-1) + i - p + 1);
		if(p < i) dp[i] = min(dp[i], dp[p] + 2 * (s-1) + i - p);
	}
	printf("%lld",dp[n] + n + 1);
}
