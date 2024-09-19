#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 100005;

vector<pi> gph[MAXN];
int T1, cuts;

int dfs(int x, int p) {
	vector<int> v;
	for (auto &[w, y] : gph[x]) {
		int k = dfs(y, x);
		if (k >= 0 && k - w < 0) {
			k = 0;
		}
		v.push_back(k - w);
	}
	sort(all(v));
	reverse(all(v));
	while (sz(v) && v[sz(v) - 1] < -T1) {
		cuts++;
		v.pop_back();
	}
	while (sz(v) >= 2 && v[sz(v) - 1] + v[sz(v) - 2] < 0) {
		cuts++;
		v.pop_back();
	}
	if (sz(v) == 0)
		return T1;
	return v.back();
}

int trial(int t) {
	T1 = t;
	cuts = 0;
	dfs(0, -1);
	return cuts + 1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int p, t;
		cin >> p >> t;
		p--;
		gph[p].push_back({t, i});
	}
	int s = 0, e = 1e9;
	while (s != e) {
		int mid = (s + e) / 2;
		if (trial(mid) > m)
			s = mid + 1;
		else
			e = mid;
	}
	cout << s << "\n";
}