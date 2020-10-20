#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, int>;

struct intv{
	int s, e; lint x;
};

vector<vector<pi>> gph;
vector<lint> dp;

int main(){
	int n;
	scanf("%d",&n);
	vector<int> a(n + 2);
	a[0] = -1.1e9;
	a[n + 1] = 2.1e9;
	vector<intv> res;
	auto sgn = [&](int x){
		return a[x] - a[x-1] <= a[x+1] - a[x];
	};
	auto add_circ = [&](int v, int x){
		res.push_back({v - x, v + x, 1ll * x * x});
	};
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=n; i++){
		int dist = min(a[i+1] - a[i], a[i] - a[i-1]);
		add_circ(a[i], dist);
	}
	 for(int i=1; i<=n; ){
		int e = i;
		while(e <= n && sgn(i) == sgn(e)) e++;
		if(i == 1 || e - 1 == n){
			i = e;
			continue;
		}
		if(sgn(i) == 1){
			int cur_rad = 0;
			for(int j = e; j >= i - 1; j--){
				cur_rad = a[j + 1] - a[j] - cur_rad;
				if(a[j] - cur_rad >= a[j - 1]) add_circ(a[j], cur_rad); 
				else break;
			}
			for(int j = i + 1; j < e; j++){
				int rd = a[j] + a[j-2] - 2 * a[j-1];
				if(a[j] - rd >= a[j - 1]) add_circ(a[j], rd);
			}
		}
		else{
			int cur_rad = 0;
			for(int j = i - 1; j <= e; j++){
				cur_rad = a[j] - a[j - 1] - cur_rad;
				if(a[j] + cur_rad <= a[j + 1]) add_circ(a[j], cur_rad);
				else break;
			}
			for(int j = i; j + 1 < e; j++){
				int rd = 2 * a[j+1] - a[j] - a[j+2];
				if(a[j] + rd <= a[j + 1]) add_circ(a[j], rd);
			}
		}
		i = e;
	}
	vector<int> crd;
	for(auto &i : res){
		crd.push_back(i.s);
		crd.push_back(i.e);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	gph.clear();
	dp.clear();
	gph.resize(sz(crd));
	dp.resize(sz(crd));
	for(auto &i : res){
		i.s = lower_bound(all(crd), i.s) - crd.begin();
		i.e = lower_bound(all(crd), i.e) - crd.begin();
		gph[i.e].emplace_back(i.x, i.s);
	}
	for(int i=1; i<sz(crd); i++){
		dp[i] = dp[i-1];
		for(auto &j : gph[i]) dp[i] = max(dp[i], dp[j.second] + j.first);
	}
	cout << dp.back() << endl;
}
