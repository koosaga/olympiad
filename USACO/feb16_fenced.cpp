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
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int A, B, n, m, a[25005], b[25005];
priority_queue<int, vector<int>, greater<int> > pq1, pq2;

int main(){
	freopen("fencedin.in","r",stdin);
	freopen("fencedin.out","w",stdout);
	scanf("%d %d %d %d",&A,&B,&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=m; i++) scanf("%d",&b[i]);
	a[n+1] = A, b[m+1] = B;
	sort(a, a+n+2);
	sort(b, b+m+2);
	for(int i=0; i<=n; i++){
		pq1.push(a[i+1] - a[i]);
	}
	for(int i=0; i<=m; i++){
		pq2.push(b[i+1] - b[i]);
	}
	lint ret = 0;
	bool cx = 0, cy = 0;
	while(!pq1.empty() || !pq2.empty()){
		if(!pq1.empty() && (pq2.empty() || pq2.top() > pq1.top())){
			if(!cy) ret += 1ll * m * pq1.top();
			else ret += 1ll * min((int)pq2.size(), m) * pq1.top();
			cy = 1;
			pq1.pop();
		}
		else{
			if(!cx) ret += 1ll * n * pq2.top();
			else ret += 1ll * min((int)pq1.size(), n) * pq2.top();
			cx = 1;
			pq2.pop();
		}
	}
	cout << ret;
}