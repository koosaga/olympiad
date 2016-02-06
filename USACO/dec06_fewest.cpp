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
const int mod = 1e6;

int n, t, v[105], c[105];
int dp[105][25005];
int dp2[105][25005];
int main(){
	cin >> n >> t;
	for(int i=1; i<=n; i++) cin >> v[i];
	for(int i=1; i<=n; i++) cin >> c[i];
	memset(dp, 0x3f, sizeof(dp));
	memset(dp2, 0x3f, sizeof(dp2));
	dp[0][0] = 0;
	dp2[0][0] = 0;
	for(int i=1; i<=n; i++){
		priority_queue<pi, vector<pi>, greater<pi> > pq[10005];
		for(int j=0; j<=t+14400; j++){
			dp2[i][j] = dp2[i-1][j];
			if(j >= v[i]) dp2[i][j] = min(dp2[i][j], dp2[i][j-v[i]] + 1);
			int p = j % v[i];
			pq[p].push(pi(dp[i-1][j] - j / v[i], j));
			while(1){
				pi t = pq[p].top();
				if(j - t.second > v[i] * c[i]){
					pq[p].pop();
					continue;
				}
				dp[i][j] = t.first + j / v[i];
				break;
			}
		}
	}
	int ret = 1e9;
	for(int i=t; i<=t+14400; i++){
		ret = min(ret, dp[n][i] + dp2[n][i-t]);
	}
	if(ret <= 1e8) cout << ret;
	else cout << -1;
}