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
typedef pair<double, double> pd;
const double eps = 1e-7;

int n;
pi a[105];

int sx = 1e9, ex = -1e9;
double px;

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

struct seg{
	int sx, sy, ex, ey;
};

double cross(seg p, seg q){
	double a = p.ey - p.sy, b = p.sx - p.ex;
	double d = q.ey - q.sy, e = q.sx - q.ex;
	double c = -a*p.sx -b*p.sy, f = -d*q.sx -e*q.sy;
	return (b * f - c * e) / (a * e - b * d);
}

double solve(pi a, pi b, pi c){
	if(ccw(a, b, c) == 0) return 0;
	return cross({a.first * 2, a.second * 2, b.first + c.first, b.second + c.second},
		{b.first * 2, b.second * 2, a.first + c.first, a.second + c.second}) / 2;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		if(a[i].second == 0) sx = min(sx, a[i].first), ex = max(ex, a[i].first);
		px = a[0].first;
	}
	double gx = 0;
	double area = 0;
	for(int i=1; i<n-1; i++){
		int tmp = ccw(a[0], a[i], a[i+1]);
		area += tmp;
		gx += solve(a[0], a[i], a[i+1]) * tmp * 0.5;
	}
	if(area < 0) area = -area, gx = -gx;
	area /= 2;
	gx /= area;
	//printf("%f\n",gx);
	double rs = 0.01, re = 1e18;
	if(fabs(sx - px) <= eps){
		if(gx - sx < -eps){
			puts("unstable");
			return 0;
		}
	}
	else{
		if(sx - px < 0){
			rs = max(rs, (gx - sx) * area / (sx - px));
		}
		else{
			re = min(re, (gx - sx) * area / (sx - px));
		}
	}
	if(fabs(ex - px) <= 1e-8){
		if(ex - gx < -1e-8){
			puts("unstable");
			return 0;
		}
	}
	else{
		if(ex > px){
			rs = max(rs, (gx - ex) * area / (ex - px));
		}
		else{
			re = min(re, (gx - ex) * area / (ex - px));
		}
	}
	if(rs > re){
		puts("unstable");
		return 0;
	}
	printf("%lld .. ", (lint)floor(rs + eps));
	if(re > 1e17) puts("inf");
	else printf("%lld", (lint)ceil(re - eps));
}