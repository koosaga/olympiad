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
typedef pair<double, double> pi;
const double eps = 1e-7;

struct line{
	int a, b, c;
}a[311];

pi cross(line a, line b){
	double det = a.a * b.b - a.b * b.a;
	if(fabs(det) < eps) return pi(-1e9, -1e9);
	return pi(1.0 * (a.b * b.c - a.c * b.b) / det, 1.0 * (a.c * b.a - a.a * b.c) / det);
}

int n, m;
vector<pi> v;

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		char t;
		int a1, a2, a3, b1, b2, b3;
		cin >> t >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
		if(t == 'J') a[i] = {a1-b1, a2-b2, a3-b3}; 
		if(t == 'B') a[i] = {b1-a1, b2-a2, b3-a3};
	}
	a[n++] = {100,0,-1};
	a[n++] = {0,100,-1};
	a[n++] = {-1,0,100};
	a[n++] = {0,-1,100};
	a[n++] = {-1,100,0};
	a[n++] = {100,-1,0};
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			pi t = cross(a[i], a[j]);
			if(t.first < -1e8) continue;
			bool bad = 0;
			for(int k=0; k<n; k++){
				if(t.first * a[k].a + t.second * a[k].b + a[k].c < -eps){
					bad = 1;
					break;
				}
			}
			if(!bad) v.push_back(t);
		}
	}
	for(int i=0; i<m; i++){
		int a1, a2, a3, b1, b2, b3;
		cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
		bool neg = 0, pos = 0;
		for(auto &j : v){
			double tmp = j.first * (a1-b1) + j.second * (a2-b2) + a3-b3;
			if(tmp <= eps) neg = 1;
			if(tmp >= -eps) pos = 1;
		}
		if(pos && neg) puts("U");
		else if(pos) puts("J");
		else if(neg) puts("B");
	}
}