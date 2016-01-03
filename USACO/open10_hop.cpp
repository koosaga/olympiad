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
typedef pair<lint, int> pi;

int n, k;
lint a[250005], s[250005], dp[250005];
priority_queue<pi> pq;

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		s[i] = s[i-1];
		if(a[i] > 0) s[i] += a[i];
	}
	pq.push(pi(0ll, 0));
	dp[1] = a[1];
	lint ret = max(0ll, max(a[1], a[k]));
	for(int i=2; i<=n; i++){
		while(pq.top().second < i-k) pq.pop();
		dp[i] = pq.top().first + a[i] + a[i-1] + s[i-2];
		ret = max(ret, dp[i]);
		pi backup(-1, -1);
		if(pq.top().second == i-k){
			backup = pq.top();
			pq.pop();
		}
		if(!pq.empty()) ret = max(ret, pq.top().first + a[i] + s[i-1]);
		if(backup.second != -1){
			pq.push(backup);
		}
		pq.push(pi(dp[i-1] - s[i-1], i-1));
	}
	cout << ret;
}