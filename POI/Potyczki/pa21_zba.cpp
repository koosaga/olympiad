#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 400005;

// X(r) - X(l) <= v
// X(i+1)- X(i) <= +1
// X(i) - X(i+1) <= 0
vector<vector<pi>> gph;

vector<lint> dijkstra(int s, int n) {
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	vector<lint> dist(n, 1e18);
	auto enq = [&](int x, lint v) {
		if (dist[x] > v) {
			dist[x] = v;
			pq.push({v, x});
		}
	};
	enq(s, 0);
	while (sz(pq)) {
		auto x = pq.top();
		pq.pop();
		if (dist[x[1]] != x[0])
			continue;
		for (auto &[w, y] : gph[x[1]])
			enq(y, w + x[0]);
	}
	return dist;
}

void add_edge(int s, int e, int x) { gph[s].push_back({x, e}); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	vector<array<int, 3>> sum(sz(s) + 1);
	for (int i = 0; i < sz(s); i++) {
		sum[i + 1] = sum[i];
		sum[i + 1][s[i] - 'a']++;
	}
	lint ans = 0;
	for (int i = 0; i < 3; i++) {
		map<pi, int> mp;
		for (int j = 1; j <= sz(s); j++) {
			mp[pi{sum[j - 1][i], sum[j - 1][(i + 1) % 3] - sum[j - 1][(i + 2) % 3]}]++;
			ans += mp[pi{sum[j][i], sum[j][(i + 1) % 3] - sum[j][(i + 2) % 3]}];
		}
	}
	map<pi, int> mp;
	for (int j = 1; j <= sz(s); j++) {
		mp[pi{sum[j - 1][1] - sum[j - 1][0], sum[j - 1][2] - sum[j - 1][0]}]++;
		ans += mp[pi{sum[j][1] - sum[j][0], sum[j][2] - sum[j][0]}];
	}
	for (int i = 0; i < sz(s);) {
		int j = i;
		while (j < sz(s) && s[i] == s[j])
			j++;
		ans += 1ll * (j - i) * (j - i + 1) / 2;
		i = j;
	}
	cout << ans << "\n";
}