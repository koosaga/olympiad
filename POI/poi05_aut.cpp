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

struct pnt{
	int x, y, w;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[100005];

int n;

vector<int> vx, vy;
int dp[100005];

struct seg{
	int tree[100005];
	void add(int x, int v){
		while(x <= n){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}seg;

int main(){
	scanf("%*d %*d %d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].w);
	}
	sort(a, a+n);
	for(int i=0; i<n; i++){
		vx.push_back(a[i].x);
		vy.push_back(a[i].y);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	for(int i=0; i<n; i++){
		a[i].x = lower_bound(vx.begin(), vx.end(), a[i].x) - vx.begin() + 1;
		a[i].y = lower_bound(vy.begin(), vy.end(), a[i].y) - vy.begin() + 1;
	}
	sort(a, a+n);
	for(int i=0; i<n; i++){
		dp[i] = seg.query(a[i].y) + a[i].w;
		seg.add(a[i].y, dp[i]);
	}
	cout << *max_element(dp, dp + n);
}
