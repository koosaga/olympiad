#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

lint solve(vector<pi> a){
	sort(all(a));
	int n = sz(a);
	if(n == 1) return 0;
	vector<lint> pmax(n);
	vector<lint> pmin(n);
	for(int i = 0; i < n; i++){
		pmax[i] = a[i].second;
		if(i) pmax[i] = max(pmax[i], pmax[i - 1]);
		pmin[i] = a[i].second;
		if(i) pmin[i] = min(pmin[i], pmin[i - 1]);
	}
	lint ret = 1e18;
	lint cmax = -1e9, cmin = 1e9;
	for(int i = n - 1; i; i--){
		cmax = max(cmax, a[i].second);
		cmin = min(cmin, a[i].second);
		lint a1 = (a[n-1].first - a[i].first) * (cmax - cmin);
		lint a2 = (a[i-1].first - a[0].first) * (pmax[i-1] - pmin[i-1]);
		ret = min(ret, max(a1, a2));
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q; cin >> q;
	while(q--){
		int n; cin >> n;
		vector<pi> a(n);
		for(auto &[x, y] : a) cin >> x >> y;
		lint ret = solve(a);
		for(auto &[x, y] : a) swap(x, y);
		ret = min(ret, solve(a));
		cout << ret << endl;
	}
}

