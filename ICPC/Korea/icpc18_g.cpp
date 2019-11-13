#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

double solve(){
	int S, a[3];
	cin >> S >> a[0] >> a[1] >> a[2];
	auto f = [&](int x){ return pow(max(x, 0), 3) / 3.0; };
	double ret = 0;
	for(int i=0; i<3; i++){
		for(int j=0; j<i; j++){
			ret += f(S) - f(S - a[i]) - f(S - a[j]) + f(S - a[i] - a[j]);
		}
	}
	return ret / pow(S, 3);
}

double sol[22];

int main(){
	int n; cin >> n;
	for(int i=1; i<=n; i++) sol[i] = solve();
	vector<int> v(n); iota(v.begin(), v.end(), 1);
	sort(v.begin(), v.end(), [&](int x, int y){
		int px = round(sol[x] * 1e9), py = round(sol[y] * 1e9);
		return pi(px, x) < pi(py, y);
	});
	for(auto &i : v) printf("%d ", i);
}
