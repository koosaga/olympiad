#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<vector<lint>> v(8, vector<lint>(n));
	vector<lint> w(8), x(n), y(n), z(n);
	for(int i = 0; i < n; i++){
		cin >> x[i] >> y[i] >> z[i];
		for(int j = 0; j < 8; j++){
			if(j & 1) v[j][i] += x[i];
			if(j & 2) v[j][i] += y[i];
			if(j & 4) v[j][i] += z[i];
		}
	}
	for(int i = 0; i < 8; i++){
		w[i] = *max_element(all(v[i]));
	}
	pi ret(1e10, -1);
	for(int i = 0; i < n; i++){
		lint ans = 0;
		for(int j = 0; j < 8; j++){
			lint cur = 0;
			if(j & 1) cur += x[i];
			if(j & 2) cur += y[i];
			if(j & 4) cur += z[i];
			ans = max(ans, w[j] - cur);
		}
		ret = min(ret, pi(ans, i));
	}
	cout << ret.first << " " << ret.second + 1<< "\n";
}
