#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using real_t = long double;
using pi = complex<real_t>;

pi crs(real_t a, real_t b, real_t c){
	real_t d = -b, e = a, f = 0;
	real_t det = a * e - b * d;
	return pi((e * c - b * f) / det, (a * f - d * c) / det);
}

int main(){
	vector<pi> punk;
	for(int i=0; i<2; i++){
		int a, b, c; 
		cin >> a >> b >> c;
		c *= 2;
		punk.push_back(crs(a, b, c));
	}
	printf("%.20Lf\n", abs(punk[0] - punk[1]));
}
