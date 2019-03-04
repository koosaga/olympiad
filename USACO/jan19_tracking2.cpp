#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;
const int mod = 1e9 + 7;
const int inf = 1e9;
#define sz(v) int((v).size())

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int n, k, a[MAXN], thres[MAXN];
vector<pi> v, w;
set<int> swp;
lint dp[MAXN];
lint pwr[MAXN];

int main(){
	freopen("tracking2.in", "r", stdin);
	freopen("tracking2.out", "w", stdout);
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++) swp.insert(i);
	for(int i=1; i<=n-k+1; i++){
		scanf("%d",&a[i]);
		v.emplace_back(a[i], i);
	}
	sort(v.rbegin(), v.rend());
	for(auto &i : v){
		auto l = swp.lower_bound(i.second);
		while(l != swp.end()){
			if(*l <= i.second + k - 1){
				thres[*l] = i.first;
				l = swp.erase(l);
			}
			else break;
		}
	}
	for(int i=1; i<=n; i++) w.emplace_back(thres[i], i);
	sort(w.begin(), w.end());
	set<int> s;
	lint ret = 1;
	int ptr = 0;
	for(int i=0; i<w.size(); ){
		while(ptr < w.size() && w[ptr].first < w[i].first){
			s.insert(w[ptr++].second);
		}
		int e = i;
		while(e < w.size() && w[i].first == w[e].first && w[i].second - i == w[e].second - e) e++;
		int l = w[i].second;
		int r = w[e-1].second;
		int st = l - k + 1;
		int ed = r;
		{
			auto itr = s.lower_bound(l);
			if(itr != s.begin()){
				itr = prev(itr);
				
				st = max(st, *itr + 1);
			}
		}
		{
			auto itr = s.upper_bound(r);
			if(itr != s.end()){
				ed = min(ed, *itr - k);
			}
		}
		st = max(st, 1);
		ed = min(ed, n - k + 1);
		if(st > ed){
			ret *= ipow(inf - w[i].first + 1, r - l + 1);
			ret %= mod;
		}
		else{
			lint tmp = 0;
			int g = inf - w[i].first;
			pwr[0] = 1;
			for(int i=1; i<=r-l+2; i++){
				pwr[i] = pwr[i-1] * g % mod;
			}
			for(int i=l; i<=r; i++) dp[i] = 0;
			lint running_sum = 0;
			for(int i=l; i<=r; i++){
				if(i <= st + k - 1) dp[i] += pwr[i-l];
				dp[i] += running_sum;
				dp[i] %= mod;
				running_sum *= g;
				if(i - k >= l) running_sum += mod - dp[i - k] * pwr[k] % mod;
				running_sum %= mod;
				running_sum += dp[i];
				running_sum %= mod;
				if(i >= ed){
					tmp += dp[i] * pwr[r-i];
					tmp %= mod;
				}
			}
			ret *= tmp;
			ret %= mod;
		}
		i = e;
	}
	cout << ret << endl;
}
