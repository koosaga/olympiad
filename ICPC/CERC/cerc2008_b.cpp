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
typedef pair<int, int> pi;

int n, d, q[1000005];
pi a[1000005];
int ret[1000005];

struct disj{
	int pa[1000005], ok[1000005], cnt;
	void init(int n){
		cnt = 0;
		for(int i=0; i<n; i++){
			pa[i] = i;
			ok[i] = 0;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void uni(int x, int y){
		x = find(x);
		y = find(y);
		if(x != y){
			pa[x] = y;
			cnt--;
		}
	}
	void activate(int x){
		ok[x] = 1;
		cnt++;
		if(x && ok[x-1]){
			uni(x-1, x);
		}
		if(x+1<n && ok[x+1]){
			uni(x+1, x);
		}
	}
}disj;

void solve(){
	scanf("%d %d",&n,&d);
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		a[i] = pi(x, i);
	};
	for(int i=0; i<d; i++){
		scanf("%d",&q[i]);
	}
	sort(a, a+n);
	int p = n-1;
	disj.init(n);
	for(int i=d-1; i>=0; i--){
		while(p >= 0 && a[p].first > q[i]){
			disj.activate(a[p--].second);
		}
		ret[i] = disj.cnt;
	}
	for(int i=0; i<d; i++){
		printf("%d ",ret[i]);
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