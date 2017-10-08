#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
double x[25], a[15], lo, hi;

double f(double s){
	double ret = 0;
	for(int i=0; i<=2*n; i++){
		ret += x[i] * pow(s, i+1) / (i+1);
	}
	ret *= acos(-1);
	return ret;
}

double integ(double s, double e){
	return f(e) - f(s);
}

int main(){
	int p = 0;
	while(~scanf("%d",&n)){
		for(int i=0; i<=n; i++){
			cin >> a[i];
		}
		for(int i=0; i<=2*n; i++){
			x[i] = 0;
		}
		for(int i=0; i<=n; i++){
			for(int j=0; j<=n; j++){
				x[i+j] += a[i] * a[j];
			}
		}
		int mk;
		cin >> lo >> hi >> mk;
		double vol = integ(lo, hi);
		printf("Case %d: %.2f\n", ++p, vol);
		vector<double> integs;
		for(int i=1; mk * i <= vol && i <= 8; i++){
			double s = lo, e = hi;
			for(int j=0; j<100; j++){
				double m = (s+e)/2;
				if(integ(lo, m) <= mk * i) s = m;
				else e = m;
			}
			integs.push_back(s);
		}
		if(integs.empty()) puts("insufficient volume");
		else{
			for(auto &i : integs) printf("%.2f ", i-lo);
			puts("");
		}
	}
}
