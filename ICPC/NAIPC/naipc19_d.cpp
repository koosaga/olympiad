#include <bits/stdc++.h>
using lint = long long;
using ll = long long;

// (0 <= x < n&& 0 < y <= k / d x + b / d)

ll count_solve(ll n, ll k, ll b, ll d){
	if(k == 0) return (b / d) * n;
	if(k >= d || b >= d){
		return 
		((k / d) * (n - 1) + 2 * (b / d)) * n / 2 + 
		count_solve(n, k % d, b % d, d);
	}
	return count_solve((k * n + b) / d, d, (k * n + b) % d, k);
}

lint solve(int p, int q, int n){
	lint ret = count_solve(n + 1, p, 0, q);
	return ret;
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		int p, q, n;
		scanf("%d %d %d",&p,&q,&n);
		lint ret = 1ll * p * n * (n + 1) / 2;
		ret -= q * solve(p, q, n);
		printf("%lld\n", ret);
	}
}
