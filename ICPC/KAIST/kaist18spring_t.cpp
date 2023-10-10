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
const int MAXN = 250005;

int n;
pi a[MAXN];
lint dp[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		lint x; int y;
		scanf("%lld %d",&x,&y);
		a[i] = pi(x + y, y);
	}
	sort(a, a+n);
	priority_queue<int> pq;
	lint sum = 0;
	for(int i=0; i<n; i++){
		sum += a[i].second;
		pq.push(a[i].second);
		while(sum > a[i].first){
			sum -= pq.top();
			pq.pop();
		}
	}
	cout << pq.size() << endl;
}
