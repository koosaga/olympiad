#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 305;
const int mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<lint> sum(n + 1);
	for(int i = 0; i < n; i++){
		int x; cin >> x;
		sum[i + 1] = sum[i] + x;
	}
	auto f = [&](int s, int e){
		return 1.0 * (sum[e] - sum[s - 1]) / (e - s + 1);
	};
	double avg = 1.0 * sum[n] / n;
	vector<pair<double, double>> g(n);
	for(int i = 0; i < n - 1; i++){
		int s = 0, e = n - 1 - i;
		while(s != e){
			int m = (s + e + 1) / 2;
			if(f(m + 1, m + i + 1) <= avg) s = m;
			else e = m - 1;
		}
		g[i].first = f(s + 1, s + i + 1);
		g[i].second = f(s + 2, s + i + 2);
	}
	g[n-1].first = g[n-1].second = avg;
	sort(all(g));
	double curmax = -1e9, ret = 1e9;
	for(int i = 0; i < n; i++){
		ret = min(ret, max(curmax, g[n-1].first) - g[i].first);
		curmax = max(curmax, g[i].second);
	}
	cout << setprecision(69) << ret << "\n";
}
