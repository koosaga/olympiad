#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int n, q, s, t;
lint a[200005], ans;

void upd(int x, int v){
	if(a[x] < 0) ans -= a[x] * t;
	else ans -= a[x] * s;
	a[x] += v;
	if(a[x] < 0) ans += a[x] * t;
	else ans += a[x] * s;
}

int main(){
	scanf("%d %d %d %d %*d",&n,&q,&s,&t);
	int prv = 0;
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		upd(i, x - prv);
		prv = x;
	}
	while(q--){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		upd(s, x);
		if(e < n) upd(e+1, -x);
		printf("%lld\n", -ans);
	}
}
