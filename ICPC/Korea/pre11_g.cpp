#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 100005;

lint dp[MAXN];

struct cht{
	vector<pi> stk;
	void clear(){
		stk.clear();
	}
	bool cmp(lint a, lint b, lint c, lint d){
		llf func = llf(a) * b - llf(c) * d;
		if(fabs(func) > 1e17) return func >= 0;
		return a * b - c * d >= 0;
	}
	bool bad(pi a, pi b, pi c){
		return cmp(a.second - b.second, c.first - b.first, b.second - c.second, b.first - a.first);
	}
	void add(lint a, lint b){
		pi p(a, b);
		while(sz(stk) >= 2 && bad(stk[sz(stk) - 2], stk.back(), p)) stk.pop_back();
		stk.push_back(p);
	}
	lint query(int x){
		int s = 0, e = sz(stk) - 1;
		while(s != e){
			int m = (s+e)/2;
			if(stk[m].first * x + stk[m].second < stk[m+1].first * x + stk[m+1].second) e = m;
			else s = m + 1;
		}
		return stk[s].first * x + stk[s].second;
	}
}cht;

void solve(){
	int n;
	scanf("%d",&n);
	vector<pi> v(n), w;
	for(int i=0; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		y = abs(y);
		v[i] = pi(x-y, x+y);
	}
	sort(all(v), [&](pi a, pi b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	for(auto &i : v){
		if(sz(w) == 0 || w.back().second < i.second){
			w.push_back(i);
		}
	}
	cht.clear();
	for(int i=1; i<=sz(w); i++){
		cht.add(-2 * w[i-1].first, dp[i-1] + 1ll * w[i-1].first * w[i-1].first);
		dp[i] = cht.query(w[i-1].second) + 1ll * w[i-1].second * w[i-1].second;
	}
	printf("%.1Lf\n", dp[sz(w)] * 0.5L);
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}
