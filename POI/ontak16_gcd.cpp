#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

lint gcd(lint x, lint y){
	return y ? gcd(y, x%y) : x;
}

int n;
lint a[300005];

vector<pi> cnd;

void dnc(int s, int e){
	if(s == e){
		cnd.push_back(pi(a[s], 1));
		return;
	}
	int m = (s+e)/2;
	dnc(s, m);
	dnc(m+1, e);
	vector<pi> l, r;
	lint g = a[m];
	int lp = m;
	for(int i=m-1; i>=s; i--){
		if(a[i] % g){
			l.push_back(pi(g, lp - i));
			g = gcd(g, a[i]);
			lp = i;
		}
	}
	l.push_back(pi(g, lp - s + 1));
	g = a[m+1];
	lp = m+1;
	for(int i=m+2; i<=e; i++){
		if(a[i] % g){
			r.push_back(pi(g, i - lp));
			g = gcd(g, a[i]);
			lp = i;
		}
	}
	r.push_back(pi(g, e + 1 - lp));
	for(auto &i : l){
		for(auto &j : r){
			cnd.push_back(pi(gcd(i.first, j.first), 1ll * i.second * j.second));
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
	}
	dnc(1, n);
	sort(cnd.begin(), cnd.end());
	vector<pi> ans;
	ans.push_back(cnd[0]);
	for(int i=1; i<cnd.size(); i++){
		if(cnd[i].first == ans.back().first){
			ans.back().second += cnd[i].second;
		}
		else{
			ans.push_back(cnd[i]);
		}
	}
	int q;
	scanf("%d",&q);
	lint prv = 0;
	while(q--){
		lint x;
		scanf("%lld",&x);
		x ^= prv;
		auto w = lower_bound(ans.begin(), ans.end(), pi(x, -1));
		if(w != ans.end() && w->first == x){
			printf("%lld\n", w->second);
			prv = w->second;
		}
		else puts("0"), prv = 0;
	}
}

