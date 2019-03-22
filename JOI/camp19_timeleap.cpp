#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 600005;
const int B = 505;

int n, q;
pi a[MAXN];

struct bucket{
	lint ints, inte;
	int destination;
	lint offset;
	bool found;
	void remake(int s, int e){
		s = max(s, 1); e = min(e, 2 * n - 1);
		ints = -1e9, inte = 2e9;
		offset = 0;
		found = 0;
		for(int i=s; i<=e; i++){
			if(max(ints, a[i].first) <= min(inte, a[i].second)){
				inte = min(inte, a[i].second);
				ints = max(ints, a[i].first);
			}
			else{
				found = 1; 
				if(a[i].first > inte) ints = inte;
				if(a[i].second < ints) inte = ints;
				int x = inte;
				for(int j=i; j<=e; j++){
					if(x < a[j].first) x = a[j].first;
					if(x > a[j].second){
						offset += x - a[j].second;
						x = a[j].second;
					}
				}
				destination = x;
				break;
			}
		}
	}
	pi process(int x){
		if(!found){
			if(x > inte) return pi(x - inte, inte);
			else return pi(0ll, max(x * 1ll, ints));
		}
		lint ret = offset + max(x - ints, 0ll);
		return pi(ret, 1ll * destination);
	}
}bkt[10000];

pi solve(int s, int e, int x){
	if(e - s <= 3*B){
		lint ans = 0;
		for(int i=s; i<=e; i++){
			if(x < a[i].first) x = a[i].first;
			if(x > a[i].second){
				ans += x - a[i].second;
				x = a[i].second;
			}
		}
		return pi(ans, x);
	}
	else{
		auto ret1 = solve(s, (s/B + 1) * B - 1, x);
		lint ans = ret1.first;
		x = ret1.second;
		for(int i=s/B+1; i<e/B; i++){
			auto nxt = bkt[i].process(x);
			ans += nxt.first;
			x = nxt.second;
		}
		auto ret2 = solve((e / B) * B, e, x);
		ans += ret2.first;
		x = ret2.second;
		return pi(ans, x);
	}
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<n; i++){
		scanf("%lld %lld",&a[i].first,&a[i].second);
		a[2*n-i] = a[i];
	}
	a[n] = pi(6, 9);
	for(int i=1; i<=2*n-1; i++){
		a[i].first -= i;
		a[i].second -= i + 1;
	}
	for(int i=0; i<=2*n-1; i+=B){
		bkt[i/B].remake(i, i + B - 1);
	}
	for(int i=0; i<q; i++){
		int t; scanf("%d",&t);
		if(t == 1){
			int p, s, e; scanf("%d %d %d",&p,&s,&e);
			a[p] = pi(s - p, e - p - 1);
			a[2*n-p] = pi(s - 2 * n + p, e - 2 * n + p - 1);
			{
				int key = p / B;
				bkt[key].remake(key * B, key * B + B - 1);
			}
			{
				int key = (2 * n - p) / B;
				bkt[key].remake(key * B, key * B + B - 1);
			}
		}
		else{
			int p, q, r, s; scanf("%d %d %d %d",&p,&q,&r,&s);
			lint ans = 0;
			if(p < r){
				q -= p;
				s -= r;
				auto dap = solve(p, r - 1, q);
				ans = dap.first + max(dap.second - s, 0ll);
			}
			else if(p > r){
				q -= 2 * n - p + 1;
				s -= 2 * n - r + 1;
				auto dap =  solve(2 * n - p + 1, 2 * n - r, q);
				ans = dap.first + max(dap.second - s, 0ll);
			}
			else{
				ans = max(q - s, 0);
			}
			printf("%lld\n", ans);
		}
	}
}
