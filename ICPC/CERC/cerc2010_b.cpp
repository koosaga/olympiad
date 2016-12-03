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
typedef pair<llf, llf> pi;
const llf inf = 1e18;

struct line{
	int a, b, c;
}a[200005];
 
int n;
 
int rcmp(int a, int b, int c, int d){
	if(1ll * a * d == 1ll * b * c) return 0;
	llf s1 = (llf)a/b;
	llf s2 = (llf)c/d;
	return s1 < s2 ? 1 : -1;
}
 
pi crs(line a, line b){
	llf det = (llf)a.a * b.b - (llf)a.b * b.a;
	llf ls = (llf)b.c * a.b - (llf)a.c * b.b;
	llf rs = (llf)b.a * a.c - (llf)a.a * b.c;
	return pi(ls / det, rs / det);
}
 
struct hull{
	vector<line> dq;
	void init(){
		dq.clear();
	}
	void add(line x){
		if(!dq.empty() && rcmp(dq.back().a, dq.back().b, x.a, x.b) == 0){
			return;
		}
		while(dq.size() >= 2 && crs(dq[dq.size()-2], dq.back()).first > crs(dq.back(), x).first){
			dq.pop_back();
		}
		dq.push_back(x);
	}
	vector<pi> getpnt(){
		vector<pi> ret;
		llf hamsu1 = (dq.front().a * -inf + dq.front().c) / (-dq.front().b);
		llf hamsu2 = (dq.back().a * inf + dq.back().c) / (-dq.back().b);
		ret.push_back(pi(-inf, hamsu1));
		for(int i=0; i<dq.size()-1; i++){
			ret.push_back(crs(dq[i], dq[i+1]));
		}
		ret.push_back(pi(inf, hamsu2));
		return ret;
	}
}hull, rhull;
 
llf dist(pi a, pi b){
	llf x = b.first - a.first;
	llf y = b.second - a.second;
	return x * x + y * y;
}

llf ccw(pi a, pi b, pi c){
	llf dx1 = b.first - a.first;
	llf dy1 = b.second - a.second;
	llf dx2 = c.first - a.first;
	llf dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

llf dot(pi a, pi b, pi c){
	llf dx1 = b.first - a.first;
	llf dy1 = b.second - a.second;
	llf dx2 = c.first - a.first;
	llf dy2 = c.second - a.second;
	return dx1 * dx2 + dy1 * dy2;
}

llf lpdist(pi l1, pi l2, pi x){
	if(dot(l1, l2, x) > 0 && dot(l2, l1, x) > 0){
		llf t = ccw(l1, l2, x);
		if(t < 0) t = -t;
		t *= t / dist(l1, l2);
		return t;
	}
	return min(dist(l1, x), dist(l2, x));
}

llf getdist(vector<pi> &v1, vector<pi> &v2){
	llf ret = inf;
	for(auto &i : v1){
		int s = 0, e = v2.size()-2;
		while(s != e){
			int m = (s+e)/2;
			if(lpdist(v2[m], v2[m+1], i) < lpdist(v2[m+1], v2[m+2], i)){
				e = m;
			}
			else s = m+1;
		}
		ret = min(ret, lpdist(v2[s], v2[s+1], i));
	}
	return ret;
}
 
void solve(){
	hull.init();
	rhull.init();
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].a,&a[i].b,&a[i].c);
	}
	sort(a, a+n, [&](const line &a, const line &b){
		if(rcmp(-a.a, a.b, -b.a, b.b) == 0){
			return rcmp(-a.c, a.b, -b.c, b.b) < 0;
		}
		return rcmp(-a.a, a.b, -b.a, b.b) > 0;
	});
	for(int i=0; i<n; i++){
		hull.add(a[i]);
		rhull.add(a[n-1-i]);
	}
	vector<pi> p1 = hull.getpnt();
	vector<pi> p2 = rhull.getpnt();
	printf("%Lf\n",min(getdist(p1, p2), getdist(p2, p1)));
}
 
int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}