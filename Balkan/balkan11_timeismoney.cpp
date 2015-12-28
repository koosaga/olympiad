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

struct edg{int s, e, x, y;}a[10005];
int n, m;

struct disj{
	int pa[205];
	void init(int n){
		for(int i=0; i<n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int cx = 1e9, cy = 1e9;
int mc1 = 1e9, mc2 = 1e9;

pi getmst(int c1, int c2, int p){
	disj.init(n);
	sort(a, a+m, [&](const edg &a, const edg &b){
		return 1ll * c1 * a.x + 1ll * c2 * a.y < 1ll * c1 * b.x + 1ll * c2 * b.y;
	});
	pi tmp(0,0);
	for(int i=0; i<m; i++){
		if(disj.uni(a[i].s, a[i].e)){
			tmp.first += a[i].x;
			tmp.second += a[i].y;
			if(p) printf("%d %d\n",a[i].s, a[i].e);
		}
	}
	if(1ll * cx * cy > 1ll * tmp.first * tmp.second){
		cx = tmp.first;
		cy = tmp.second;
		mc1 = c1, mc2 = c2;
	}
	return tmp;
}

bool ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 >= 1ll * dy1 * dx2;
}

void solve(pi s, pi e){
	pi m = getmst(s.second - e.second, e.first - s.first, 0);
	if(!ccw(e, m, s)) solve(s, m), solve(m, e);
}

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		cin >> a[i].s >> a[i].e >> a[i].x >> a[i].y;
	}
	pi upper = getmst(1, 0, 0); // x is low
	pi lower = getmst(0, 1, 0); // y is low
	solve(upper, lower);
	printf("%d %d\n",cx,cy);
	getmst(mc1, mc2, 1);
}