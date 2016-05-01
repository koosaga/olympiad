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
 
int n, k;
pi a[505];
double px, py;
double pd[505][505], pang[505][505];


bool trial(double r){
	for(int i=0; i<n; i++){
		map<double, int> add;
		for(int j=0; j<n; j++){
			if(i == j) continue;
			double d = pd[i][j];
			double ang = pang[i][j];
			if(d > 2.0 * r + 1e-8) continue;
			double dx = acos((d - 1e-8) / (2.0 * r));
			double st = ang - dx, ed = ang + dx;
			while(st < 0){
				st += 2 * PI;
				ed += 2 * PI;
			}
			add[st]++;
			add[ed]--;
			if(ed < 2 * PI){
				add[st+2*PI]++;
				add[ed+2*PI]--;
			}
		}
		int sum = 0;
		for(auto &j : add){
			sum += j.second;
			if(sum + 1 >= k){
				px = a[i].first + r * cos(j.first);
				py = a[i].second + r * sin(j.first);
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j) continue;
			pd[i][j] = hypot(a[j].first - a[i].first, a[j].second - a[i].second);
			pang[i][j] = atan2(a[j].second - a[i].second, a[j].first - a[i].first);
		}
	}
	double s = 0, e = 1e5;
	for(int i=0; i<30; i++){
		double m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m;
	}
	printf("%.10f\n%.10f %.10f",s, px, py);
}