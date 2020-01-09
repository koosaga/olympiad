#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

int mod;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int n, a[MAXN], dp[MAXN];
vector<pi> bs;

int trial(int q){
	int ret = 1;
	for(int i=n-1; i>=0; i--){
		dp[i] = 1;
		auto jv = lower_bound(all(bs), pi(1ll * a[i] * q % mod, i + 1));
		if(jv == bs.end() || jv->first != 1ll * a[i] * q % mod) continue;
		dp[i] = dp[jv->second] + 1;
		ret = max(ret, dp[i]);
	}
	return ret;
}

void solve(){
	bs.clear();
	scanf("%d",&n);
	scanf("%d",&mod);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		bs.emplace_back(a[i], i);
	}
	sort(all(bs));
	vector<lint> ans;
	for(int i=0; i<n; i++){
		lint inv = ipow(a[i], mod - 2);
		for(int j=i+1; j<i+5&&j<n; j++){
			ans.push_back(inv * a[j] % mod);
		}
	}
	sort(all(ans));
	vector<pi> w;
	for(int i=0; i<sz(ans); ){
		int e = i;
		while(e < sz(ans) && ans[e] == ans[i]) e++;
		w.emplace_back(e - i, ans[i]);
		i = e;
	}
	sort(all(w));
	reverse(all(w));
	int ret = 0;
	for(int i=0; i<10 && i<sz(w); i++) ret = max(ret, trial(w[i].second));
	if(ret <= (n - 1) / 2) puts("-1");
	else printf("%d\n", ret);
}

int main(){
	int tc; scanf("%d",&tc);
	for(int i=0; i<tc; i++){
		solve();
	}
}

