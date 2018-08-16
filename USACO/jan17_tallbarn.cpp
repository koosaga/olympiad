#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

llf sum;
lint n, k, a[100005], b[100005], cur;

bool trial(llf x){
	sum = 0;
	cur = 0;
	for(int i=0; i<n; i++){
		llf t = sqrt(a[i] / x + 0.25) + 0.5 + 1e-12;
		if(t > 1e13) return 0;
		b[i] = (lint)floor(t);
		cur += b[i];
		if(cur > k) return 0;
		sum += (llf)a[i] / b[i];
	}
	return 1;
}

int main(){
	scanf("%lld %lld",&n,&k);
	for(int i=0; i<n; i++) scanf("%lld",&a[i]);
	sort(a, a+n);
	reverse(a, a+n);
	llf st = 0, ed = 1e12;
	for(int i=0; i<100; i++){
		llf mi = (st + ed) / 2;
		if(trial(mi)) ed = mi;
		else st = mi;
	}
	assert(trial(ed));
	for(int i=0; i<n; i++){
		if(cur < k){
			sum += (llf)a[i] / (b[i] + 1) - (llf)a[i] / b[i];
			cur++;
		}
	}
	printf("%.0Lf", sum);
}


