#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

lint W, ans;

lint dfs() {
	int m, ch;
	cin >> m >> ch;
	vector<lint> v;
	for (int j = 0; j < ch; j++) {
		auto Q = dfs();
		ans += Q / W;
		v.push_back(Q % W);
	}
	sort(all(v));
	int p = 0;
	lint sum = 0;
	while (p < sz(v) && sum + v[p] <= W)
		sum += v[p++];
	ans += sz(v) - p;
	return sum + m;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> W;
	lint z = dfs();
	ans += (z - 1) / W + 1;
	cout << ans << "\n";
}