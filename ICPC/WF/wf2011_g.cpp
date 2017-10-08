#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;

int n, a[505];

double solve(int s, int e){
	if(e - s < 2) return 0;
	int mx = max_element(a+s, a+e+1) - a;
	int sm = 0;
	for(int i=s; i<=e; i++){
		sm += a[i];
	}
	double ret = solve(s, mx-1) + solve(mx+1, e);
	if(sm <= 2 * a[mx]) return ret;
	auto trial = [&](double x){
		double ret = 0;
		for(int i=s; i<=e; i++){
			ret += acos(1 - a[i] * a[i] / (2 * x * x));
		}
		return ret;
	};
	double tmp = 0;
	if(trial(a[mx] * 0.5 + 1e-9) < 2 * M_PI){
		double st = a[mx] * 0.5 + 1e-9, ed = 1e6;
		for(int i=0; i<70; i++){
			double m = (st+ed)/2;
			double tmp = acos(1 - a[mx] * a[mx] / (2 * m * m));
			if(trial(m) - 2 * tmp < 0) st = m;
			else ed = m;
		}
		for(int i=s; i<=e; i++){
			double ang = acos(1 - a[i] * a[i] / (2 * st * st));
			if(mx == i) tmp -= 0.5 * st * st * sin(ang);
			else tmp += 0.5 * st * st * sin(ang);
		}
	}
	else{
		double st = a[mx] * 0.5, ed = 1e6;
		for(int i=0; i<70; i++){
			double m = (st+ed)/2;
			if(trial(m) < 2 * M_PI) ed = m;
			else st = m;
		}
		for(int i=s; i<=e; i++){
			double ang = acos(1 - a[i] * a[i] / (2 * st * st));
			tmp += 0.5 * st * st * sin(ang);
		}
	}
	return max(ret, tmp);
}

int main(){
	int tc = 0;
	while(1){
		cin >> n;
		if(!n) break;
		for(int i=0; i<n; i++) cin >> a[i];
		printf("Case %d: %.10f\n", ++tc, solve(0, n-1));
	}
}
