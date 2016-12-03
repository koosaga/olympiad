#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

int n, m;
int nxt[1000005];
bool vis[1000005];
int ret[1000005];
pi a[1000005];
int ori[1000005];

void solve(){
	scanf("%d %d",&n,&m);
	fill(vis+1, vis + n + 1, 1);
	fill(nxt, nxt + m + 1, 987654321);
	for(int i=1; i<=m; i++){
		scanf("%d",&ori[i]);
		a[i] = pi(ori[i], i);
	}
	sort(a+1, a+m+1);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=1; i<=m; i++){
		if(a[i].first == 0) continue;
		if(a[i].first != a[i-1].first){
			pq.push(pi(a[i].second, a[i].first));
		}
		else{
			nxt[a[i-1].second] = a[i].second;
		}
	}
	for(int i=1; i<=m; i++){
		if(ori[i]){
			if(vis[ori[i]]){
				puts("NO");
				return;
			}
			pq.push(pi(nxt[i], ori[i]));
			vis[ori[i]] = 1;
		}
		else{
			if(pq.empty()){
				ret[i] = 0;
				continue;
			}
			pi t = pq.top();
			pq.pop();
			ret[i] = t.second;
			vis[t.second] = 0;
		}
	}
	puts("YES");
	for(int i=1; i<=m; i++){
		if(!ori[i]) printf("%d ",ret[i]);
	}
	puts("");
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
}