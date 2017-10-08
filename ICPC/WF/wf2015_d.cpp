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

int n, s;
double z[10005], r[10005];

double integrate(double s, double e, int idx){
	if(s > e) return 0;
	double ep = r[idx] * r[idx] * e - e * e * e / 3;
	double sp = r[idx] * r[idx] * s - s * s * s / 3;
	return acos(-1) * (ep - sp);
}

double getVol(double l){
	double ret = 0;
	for(int i=0; i<n; i++){
		ret += integrate(-r[i], min(l - z[i], r[i]), i);
	}
	return 10000.0 * l - ret;
}

int main(){
	scanf("%d %d",&n,&s);
	for(int i=0; i<n; i++){
		scanf("%lf %*lf %*lf %lf",&r[i],&z[i]);
		z[i] /= 1000, r[i] /= 1000;
	}
	double prev = 0, full = getVol(100);
	for(int i=1; i<=s; i++){
		double vol = full * i / s;
		double s = 0, e = 100;
		for(int j=0; j<30; j++){
			double m = (s+e)/2;
			if(getVol(m) <= vol) s = m;
			else e = m;
		}
		printf("%.9f\n",e - prev);
		prev = e;
	}
}