#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

int n;
int a[2][20];

int main(){
	cin >> n;
	for(int i=0; i<2; i++){
		for(int j=0; j<n; j++){
			cin >> a[i][j];
		}
	}
	vector<pi> ans;
	for(int i=0; i<(1<<n); i++){
		lint cnt[2] = {};
		for(int j=0; j<n; j++){
			cnt[(i >> j) & 1] += a[(i >> j) & 1][j];
		}
		ans.emplace_back(cnt[0], cnt[1]);
	}
	sort(ans.rbegin(), ans.rend());
	vector<pi> sky;
	for(auto &i : ans){
		if(sky.empty() || sky.back().second < i.second){
			sky.push_back(i);
		}
	}
	pi ret(1e18, 1e18);
	for(int i=1; i<sky.size(); i++){
		lint l = sky[i].first + 1;
		lint r = sky[i - 1].second + 1;
		ret = min(ret, pi(l + r, r));
	}
	cout << ret.first - ret.second << endl;
	cout << ret.second << endl;
}
