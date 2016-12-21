#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef pair<llf, llf> pj;
const llf eps = 1e-10;

pi c, a[40005];
int r, n;

llf ccw(pj a, pj b){
	return a.first * b.second - b.first * a.second;
}

llf solve2(pj x, pj y){
	llf ang = atan2(y.second, y.first) - atan2(x.second, x.first) + 4 * M_PI;
	while(ang >= M_PI) ang -= 2 * M_PI;
	return 0.5 * min(ccw(x, y), ang * r * r);
}

llf solve(pj x, pj y){
	if(fabs(ccw(x, y)) < 0.1) return 0;
	if(ccw(x, y) < 0) return -solve(y, x);
	llf dis = hypot(y.first - x.first, y.second - x.second);
	llf linepnt = ccw(x, y) / dis;
	if(linepnt >= r - eps) return solve2(x, y);
	llf cx = -linepnt * (x.second - y.second) / dis;
	llf cy = -linepnt * (y.first - x.first) / dis;
	llf up = sqrt(1.0 * r * r - linepnt * linepnt) / dis;
	pj c1(cx + up * (y.first - x.first), cy + up * (y.second - x.second));
	pj c2(cx - up * (y.first - x.first), cy - up * (y.second - x.second));
	if(ccw(c1, c2) < 0) swap(c1, c2);
	vector<pj> v;
	v.push_back(x);
	if(ccw(x, c1) > 0 && ccw(c1, y) > 0) v.push_back(c1);
	if(ccw(x, c2) > 0 && ccw(c2, y) > 0) v.push_back(c2);
	v.push_back(y);
	llf ret = 0;
	for(int i=0; i<v.size()-1; i++){
		ret += solve2(v[i], v[i+1]);
	}
	return ret;
}

int main(){
	cin >> c.first >> c.second >> r >> n;
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		a[i].first -= c.first;
		a[i].second -= c.second;
	}
	a[n] = a[0];
	llf ret = 0;
	for(int i=0; i<n; i++){
		if(a[i] == a[i+1]) continue;
		ret += solve(pj(a[i].first, a[i].second), pj(a[i+1].first, a[i+1].second));
	}
	if(ret < 0) ret *= -1;
	printf("%.10f", (double)ret);
}
