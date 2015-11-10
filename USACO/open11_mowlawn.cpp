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
typedef pair<lint, int> pi;

lint dp[100005], sum;
int n, k;

priority_queue<pi, vector<pi>, greater<pi> > pq;

int main(){
	scanf("%d %d",&n,&k);
	pq.push(pi(0, 0));
	for(int i=1; i<=n+1; i++){
		int x = 0;
		if(i <= n) scanf("%d",&x);
		sum += x;
		while(pq.top().second < i - k - 1) pq.pop();
		dp[i] = pq.top().first + x;
		pq.push(pi(dp[i], i));
	}
	printf("%lld",sum - dp[n+1]);
}