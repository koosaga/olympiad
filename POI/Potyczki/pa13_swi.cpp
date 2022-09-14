#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	vector<pi> a[2];
	a[0].resize(n); a[1].resize(n);
	for(int i = 0; i < n; i++){
		cin >> a[0][i].first >> a[1][i].first >> a[0][i].second >> a[1][i].second;
	}
	auto f = [&](double t){
		double ans = 0;
		for(int i = 0; i < 2; i++){
			double mx = -1e20, mn = 1e20;
			for(int j = 0; j < n; j++){
				double eval = a[i][j].first + a[i][j].second * t;
				mx = max(mx, eval);
				mn = min(mn, eval);
			}
			ans = max(ans, mx - mn);
		}
		return ans;
	};
	double s = 0, e = 1e13;
	for(int i = 0; i < 155; i++){
		double m1 = (2 * s + e) / 3;
		double m2 = (s + 2 * e) / 3;
		if(f(m1) < f(m2)) e = m2;
		else s = m1;
	}
	cout << setprecision(69) << f((s + e) / 2) << "\n";
}
