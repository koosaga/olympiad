#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

llf sum;
lint cur;

lint n, k, a[100005];

bool trial(llf x){
	sum = 0;
	cur = 0;
	for(int i=0; i<n; i++){
		llf t = sqrt(a[i] / x + 0.25) + 0.5 + 1e-12;
		if(t > 1e13) return 0;
		lint occ = floor(t);
		if(occ + cur > k) return 0;
		cur += occ;
		sum += (llf)a[i] / occ;
	}
	return 1;
}

int main(){
	freopen("tallbarn.in", "r", stdin);
	freopen("tallbarn.out", "w", stdout);
	scanf("%lld %lld",&n,&k);
	for(int i=0; i<n; i++) scanf("%lld",&a[i]);
	llf st = 0, ed = 1e12;
	for(int i=0; i<100; i++){
		llf mi = (st + ed) / 2;
		if(trial(mi)) ed = mi;
		else st = mi;
	}
	trial(ed);
	printf("%.0Lf", sum);
}
