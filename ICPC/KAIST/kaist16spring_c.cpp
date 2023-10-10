#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;

int n, x, y;
int a[200005], b[200005], w[200005];
double opta, optb;

double trial(double t){
	double lim = 1e18;
	for(int i=0; i<n; i++){
		double tmp = t * a[i] + (1-t) * b[i];
		lim = min(lim, 1.0 * w[i] / tmp);
	}
	opta = t * lim;
	optb = (1-t) * lim;
	return x * opta + y * optb;
}

int main(){
	cin >> n >> x >> y;
	for(int i=0; i<n; i++){
		cin >> a[i];
	}
	for(int i=0; i<n; i++){
		cin >> b[i];
	}
	for(int i=0; i<n; i++){
		cin >> w[i];
	}
	double s = 0, e = 1;
	for(int i=0; i<100; i++){
		double m0 = (2*s+e)/3;
		double m1 = (s+2*e)/3;
		if(trial(m0) < trial(m1)) s = m0;
		else e = m1;
	}
	printf("%.2f\n", trial(s));
	printf("%.2f %.2f", opta, optb);
}