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
typedef pair<int, int> pi;
const double PI = acos(-1);
 
int n;
double r;
double px, py;
pi a[1005];
 
int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	lint ret = 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
	if(ret != 0) return ret > 0 ? 1 : -1;
	return 0;
}
 
lint dist(pi a, pi b){
	int dx = b.first - a.first;
	int dy = b.second - a.second;
	return 1ll * dx * dx + 1ll * dy * dy;
}
 
bool solve(){
	for(int i=0; i<n; i++){
		map<double, int> add;
		for(int j=0; j<n; j++){
			if(i == j) continue;
			double d = hypot(a[j].first - a[i].first, a[j].second - a[i].second);
			double ang = atan2(a[j].second - a[i].second, a[j].first - a[i].first);
			if(d > 2.0 * r) continue;
			double dx = fabs(acos(d / (2.0 * r)));
			double st = ang - dx, ed = ang + dx;
			while(st < 0){
				st += 2 * PI;
				ed += 2 * PI;
			}
			add[st]++;
			add[ed]--;
			if(ed <= 2 * PI){
				add[st+2*PI]++;
				add[ed+2*PI]--;
			}
		}
		int sum = 0;
		for(auto &j : add){
			sum += j.second;
			if(sum == n-1){
				px = a[i].first + r * cos(j.first);
				py = a[i].second + r * sin(j.first);
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
	}
	swap(a[0], *min_element(a, a+n));
	sort(a+1, a+n, [&](const pi &p, const pi &q){
		int t = ccw(a[0], p, q);
		if(t == 0) return dist(a[0], p) < dist(a[0], q);
		return t > 0;
	});
	int p = n-1;
	while(p > 0 && ccw(a[n-1], a[n-2], a[p-1]) == 0) p--;
	reverse(a+p+1, a+n);
	vector<pi> h;
	for(int i=0; i<n; i++){
		while(h.size() >= 2 && ccw(h[h.size()-2], h.back(), a[i]) <= 0){
			h.pop_back();
		}
		h.push_back(a[i]);
	}
	n = h.size();
	for(int i=0; i<n; i++){
		a[i] = h[i];
	}
	double s = 0, e = 1e5;
	for(int i=0; i<80; i++){
		double m = (s+e)/2;
		r = m;
		if(solve()) e = m;
		else s = m;
	}
	r = s;
	printf("%.3f %.3f\n%.3f",px+1e-5,py+1e-5,r);
}
 