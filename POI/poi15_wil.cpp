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

const int MAXN = 2000005;

int n, d, a[MAXN];
lint p, s[MAXN];

int main()
{
	scanf("%d %lld %d",&n,&p,&d);
	for(int i=1; i<=n; i++){
		scanf("%lld",&s[i]);
		s[i] += s[i-1];
	}
	priority_queue<pi> pq;
	int e = d, ans = 0;
	pq.push(pi(s[d], 1));
	for(int i=1; i<=n; i++){
		while(!pq.empty() && pq.top().second < i) pq.pop();
		while(e < n && (s[e+1] - s[i-1] - max(pq.top().first, s[e+1] - s[e+1-d]) <= p)){
			pq.push(pi(s[e+1] - s[e+1-d], e+2-d));
			e++;
		}
		ans = max(ans, e - i + 1);
	}
	printf("%d\n", ans);
}