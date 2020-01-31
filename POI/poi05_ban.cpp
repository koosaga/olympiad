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

int n, k, b[205], c[205];
int dp[205][20005], tra[205][20005];
int cnt[205];

deque<pi> dq[20005];

int main(){
	cin >> n;
	for(int i=1; i<=n; i++) cin >> b[i];
	for(int i=1; i<=n; i++) cin >> c[i];
	cin >> k;
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=n; i++){
		for(int i=0; i<20005; i++) dq[i].clear();
		for(int j=0; j<=k; j++){
			if(!dq[j % b[i]].empty() && dq[j % b[i]][0].second + c[i] * b[i] < j){
				dq[j % b[i]].pop_front();
			}
			while(!dq[j % b[i]].empty() && dq[j % b[i]].back().first > dp[i-1][j] - j / b[i]){
				dq[j % b[i]].pop_back();
			}
			dq[j % b[i]].push_back(pi(dp[i-1][j] - j / b[i], j));
			dp[i][j] = dq[j % b[i]][0].first + j / b[i];
			tra[i][j] = dq[j % b[i]][0].second;
		}
	}
	cout << dp[n][k] << endl;
	for(int i=n; i; i--){
		int dx = k - tra[i][k];
		cnt[i] = dx / b[i];
		k = tra[i][k];
	}
	for(int i=1; i<=n; i++) printf("%d ", cnt[i]);
}
