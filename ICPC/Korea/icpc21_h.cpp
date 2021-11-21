#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int MAXT = 270000;

lint solve(vector<lint> a, int d, int w){
	if(w == sz(a)){
		for(auto &i : a) i = -i;
		return solve(a, d, 0);
	}
	if(w == 0){
		if(*min_element(all(a)) < 0) return 1e18;
		lint ret = *max_element(all(a));
		if(ret != a[d]) ret = 1e18;
		return ret;
	}
	if(a[d] < 0){
		for(auto &i : a) i = -i;
		return solve(a, d, sz(a) - w);
	}
	int L = 0, R = a[d];
	a.erase(a.begin() + d);
	sort(all(a));
	int cnt_low = 0;
	int cnt_high = 0;
	int cnt_med = 0;
	for(auto &i : a){
		if(i < L) cnt_low++;
		else if(i > R) cnt_high++;
		else cnt_med++;
	}
	lint minv = min(0ll, a[0]);
	lint maxv = max(1ll * R, a[sz(a) - 1]);
	if(w == 1 && cnt_low && cnt_high){
		if(cnt_med == 0){
			return 2 * (maxv - minv) + R - L;
		}
		return 1e18;
	}
	lint ret = (maxv - minv) + (0 - minv) + (maxv - R);
	vector<lint> v;
	for(int i = 0; i < sz(a) - 1; i++){
		if(a[i] >= L && a[i + 1] <= R) v.push_back(a[i + 1] - a[i]);
	}
	sort(all(v));
//	cout << w << ' ' << cnt_low << ' ' << cnt_high << ' ' << sz(v) << endl;
//	cout << minv << ' ' << maxv << ' ' << R << endl;
	for(int i = 0; i < sz(v) && w > cnt_low + cnt_high; i++){
		w--;
		ret += 2 * v[i];
	}
	if(w > cnt_low + cnt_high) return 1e18;
	return ret;
}

lint solve2(vector<lint> a, int w){
	if(w == sz(a)){
		for(auto &i : a) i = -i;
		return solve2(a, 0);
	}
	if(w == 0){
		if(*min_element(all(a)) < 0) return 1e18;
		return *max_element(all(a));
	}
	lint ans = 1e18;
	int n = sz(a);
	for(int i = 0; i < 2; i++){
		sort(all(a));
		int cnt_low = 0, cnt_high = 0;
		for(auto &i : a){
			if(i < 0) cnt_low++;
			else cnt_high++;
		}
		if(cnt_low >= w){
			ans = min(ans, 0 + max(0ll, a[n - 1]) - 2 * min(0ll, a[0]));
		}
		else if(w == n - 1){
			auto x = *lower_bound(all(a), 0);
			ans = min(ans, 2 * max(0ll, a[n - 1]) - 2 * min(0ll, a[0]) - x);
		}
		else{
			int gamma = w - cnt_low;
			int p = 0;
			while(p < sz(a) && a[p] < 0) p++;
			set<pi> pq;
			for(int i = p; i < n - 1; i++){
				pq.emplace(a[i + 1] - a[i], i);
			}
			lint sum = 0;
			auto it = pq.begin();
			for(int i = 0; i < gamma + 1; i++){
				sum += (it->first);
				it++;
			}
			while(it != pq.end()) it = pq.erase(it);
			for(int i = n - 1; gamma - (n - 1 - i) >= 0; i--){
				lint extra = a[n - 1] - a[i];
				int need_redeem = gamma - (n - 1 - i);
				if(i > p && pq.count(pi(a[i] - a[i-1], i-1))){
					sum -= (a[i] - a[i-1]);
					pq.erase(pi(a[i] - a[i-1], i-1));
				}
				while(sz(pq) > need_redeem){
					sum -= (pq.rbegin()->first);
					pq.erase(--pq.end());
				}
				ans = min(ans, extra + 2 * sum + 0 + max(0ll, a[n - 1]) - 2 * min(0ll, a[0]));
			}
		}
		for(auto &i : a) i = -i;
		w = sz(a) - w;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, w, t;
	cin >> n >> w >> t;
	vector<lint> a(n);
	for(auto &i : a) cin >> i;
	if(t == 2){
		lint ret = solve(a, n - 1, w);
		if(ret > 1e17) ret = -1;
		cout << ret << endl;
	}
	else{
		lint ret = solve2(a, w);
		if(ret > 1e17) ret = -1;
		cout << ret << endl;
	}
}
