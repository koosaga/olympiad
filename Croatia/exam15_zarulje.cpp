#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 200005;
const int mod = 1e9 + 7;

lint ipow(lint x, lint p){
	lint ret = 1, piv = x % mod;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret % mod;
}

int n, k, a[MAXN];
int l[MAXN], r[MAXN];
lint fact[MAXN], invf[MAXN], ans[MAXN];
pi b[MAXN];

lint bino(int x, int y){
	return fact[x] * (invf[y] * invf[x-y] % mod) % mod;
}

int main(){
	scanf("%d %d",&n,&k);
	fact[0] = invf[0] = 1;
	for(int i=0; i<n; i++){
		fact[i + 1] = fact[i] * (i + 1) % mod;
		invf[i + 1] = ipow(fact[i + 1], mod - 2);
		scanf("%d",&a[i]);
		b[i] = pi(a[i], i);
	}
	stack<int> stk;
	for(int i=0; i<n; i++){
		while(!stk.empty() && a[stk.top()] > a[i]){
			r[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while(!stk.empty()){
		r[stk.top()] = n;
		stk.pop();
	}
	for(int i=n-1; i>=0; i--){
		while(!stk.empty() && a[stk.top()] > a[i]){
			l[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while(!stk.empty()){
		l[stk.top()] = -1;
		stk.pop();
	}
	sort(b, b+n);
	fill(ans, ans + n, 1);
	for(int i=0; i<n; ){
		int e = i;
		while(e < n && b[e].first == b[i].first) e++;
		vector<pi> swp;
		for(int j=i; j<e; j++){
			int pos = b[j].second;
			swp.push_back(pi(l[pos], 2));
			swp.push_back(pi(pos, -2));
			swp.push_back(pi(pos + 1, 1));
			swp.push_back(pi(r[pos] + 1, -1));
		}
		int cnt1 = 0, cnt2 = 0;
		sort(swp.begin(), swp.end());
		for(int i=0; i<swp.size(); ){
			int e = i;
			while(e < swp.size() && swp[e].first == swp[i].first){
				if(abs(swp[e].second) == 2) cnt2 += swp[e].second / 2;
				else cnt1 += swp[e].second;
				e++;
			}
			if(e < swp.size()){
				lint k = bino(cnt1 + cnt2, cnt1);
				int st = swp[i].first;
				int ed = swp[e].first;
				st = max(st, 0);
				if(st < ed){
					ans[st] *= k;
					ans[ed] *= ipow(k, mod - 2);
					ans[st] %= mod;
					ans[ed] %= mod;
				}
			}
			i = e;
		}
		i = e;
	}
	for(int i=0; i<n; i++){
		ans[i+1] *= ans[i];
		ans[i+1] %= mod;
	}
	for(int i=0; i<k; i++){
		int x;
		scanf("%d",&x);
		printf("%lld\n", ans[x-1]);
	}
}
