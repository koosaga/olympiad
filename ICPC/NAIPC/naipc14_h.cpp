#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using real_t = double;
using pi = pair<int, int>;
const int mod = 1e9 + 7;

int n;
pi a[MAXN];

real_t trial(real_t x){
	real_t up = -1e18, dn = 1e18;
	for(int i=0; i<n; i++){
		up = max(up, a[i].first * x + a[i].second);
		dn = min(dn, a[i].first * x + a[i].second);
	}
//	printf("%.10Lf = %.10Lf\n", x, up - dn);
	return up - dn;
}

real_t solve(){
	real_t s = 0, e = 1e10;
	for(int i=0; i<100; i++){
		real_t m1 = (2 * s + e) / 3;
		real_t m2 = (s + 2 * e) / 3;
		if(trial(m1) > trial(m2)) s = m1;
		else e = m2;
	}
	return trial((s + e) / 2);
}

int main(){
	while(true){
		scanf("%d",&n);
		if(n == 0) break;
		for(int j=0; j<n; j++){
			scanf("%d %d",&a[j].second,&a[j].first);
		}
		printf("%.2f\n", solve());
	}
}
