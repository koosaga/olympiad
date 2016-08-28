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
typedef pair<lint, int> pi;

lint a[2005], dp[2005][2005];
int n, m;

priority_queue<pi, vector<pi>, greater<pi> > pq1[2005], pq2[2005];
int pnt[2005];

int main(){
	cin >> m >> n;
	m++;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		a[i]++;
		a[i] += a[i-1];
	}
	for(int i=n; i; i--){
		for(int j=i; j<=n; j++){
			dp[i][j] = 1e18;
			if(a[j] - a[i-1] > m) continue;
			if(j == n){
				dp[i][j] = 0;
				continue;
			}
			while(pnt[j+1] <= n && 2ll * a[j] - a[i-1] > a[pnt[j+1]]){
				int k = pnt[j+1];
				pq1[j+1].push(pi(dp[j+1][k] - a[k] + 2ll * a[j], k));
				pnt[j+1]++;
			}
			if(!pq1[j+1].empty()){
				dp[i][j] = pq1[j+1].top().first - a[i-1];
			}
			while(!pq2[j+1].empty() && pq2[j+1].top().second < pnt[j+1]){
				pq2[j+1].pop();
			}
			if(!pq2[j+1].empty()){
				dp[i][j] = min(dp[i][j], pq2[j+1].top().first + a[i-1]);
			}
		}
		pnt[i] = i;
		for(int j=i; j<=n; j++){
			pq2[i].push(pi(dp[i][j] + a[j] - 2ll * a[i-1], j));
		}
		/*for(int j=i; j<=n; j++){
			seg1[i].add(j, dp[i][j] - a[j] + 2ll * a[i-1]);
			seg2[i].add(j, dp[i][j] + a[j] - 2ll * a[i-1]);
		}*/
	}
	cout << *min_element(dp[1] + 1, dp[1] + n + 1);
}
