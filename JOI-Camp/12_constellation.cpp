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
const int mod = 1e9 + 7;

struct pt{int x, y, c;}a[100005];

bool operator<(pt a, pt b){
	return pi(a.x, a.y) < pi(b.x, b.y);
}

bool ccw(pt p, pt q, pt r){
	int dx1 = q.x - p.x;
	int dy1 = q.y - p.y;
	int dx2 = r.x - p.x;
	int dy2 = r.y - p.y;
	return 1ll * dx1 * dy2 > 1ll * dy1 * dx2;
}

bool cmp(pt p, pt q){
	return ccw(a[0], p, q);
}

int n;
vector<pt> hull;
int cnt1, cnt2;
int sum1[200005], sum2[200005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].c);
		if(a[i].c == 1) cnt1++;
		if(a[i].c == 2) cnt2++;
	}
	swap(a[0], *min_element(a,a+n));
	sort(a+1, a+n, cmp);
	int ret1 = 1;
	int ret2 = 0;
	for(int i=0; i<n; i++){
		while(hull.size() >= 2 && !ccw(hull[hull.size() - 2], hull.back(), a[i])){
			if(hull.back().c == 0) ret1 = (ret1 * 2) % mod;
			hull.pop_back();
		}
		hull.push_back(a[i]);
	}
	int t = hull.size();
	int hcnt1 = 0, hcnt2 = 0;
	for(int i=0; i<t; i++){
		if(hull[i].c == 1) hcnt1++;
		if(hull[i].c == 2) hcnt2++;
		hull.push_back(hull[i]);
	}
	for(int i=0; i<2*t; i++){
		sum1[i] = (i ? sum1[i-1] : 0) + (hull[i].c == 1);
		sum2[i] = (i ? sum2[i-1] : 0) + (hull[i].c == 2);
	}
	if(hcnt1 == 0) ret2++;
	if(hcnt2 == 0) ret2++; 
	for(int i=0; i<t; i++){
		int low = lower_bound(sum1, sum1 + 2*t, (i ? sum1[i-1] : 0) + hcnt1) - sum1;
		int low2 = lower_bound(sum2, sum2 + 2*t, (i ? sum2[i-1] : 0) + 1) - sum2;
		ret2 += max(0, min(i + t - 1, low2) - max(i, low));
		ret2 %= mod;
	}
	lint ret = 1ll * ret1 * ret2 - (cnt1 == 0) - (cnt2 == 0) + mod;
	ret %= mod;
	printf("%lld",ret);
}