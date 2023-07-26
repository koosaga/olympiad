#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct point {
	lint first;
	lint second;
	int cnt;
};

struct cht {
	vector<point> v;
	int p = 0;
	void clear() {
		v.clear();
		p = 0;
	}
	bool parksanghoon(point a, point b, point c) { return (b.second - a.second) * (c.first - b.first) > (c.second - b.second) * (b.first - a.first); }
	void add_line(int x, lint y, int z) {
		while (v.size() >= p + 2 && parksanghoon(v[v.size() - 2], v.back(), (point){x, y, z})) {
			v.pop_back();
		}
		v.push_back({x, y, z});
	}
	pi query(int x) {
		if (sz(v) == 0)
			return pi{lint(1e18), -1};
		auto f = [&](int p) { return v[p].first * x + v[p].second; };
		while (p + 1 < sz(v) && f(p) > f(p + 1))
			p++;
		return pi{v[p].first * x + v[p].second, v[p].cnt};
	}
} cht;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	string s;
	cin >> n >> k >> s;
	vector<int> h(n);
	vector<lint> sum(n + 1);
	int x = 0, y = 0;
	for (int i = 0; i < n * 2; i++) {
		if (s[i] == 'A')
			h[x++] = y;
		else
			y++;
	}
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + h[i - 1];
	vector<int> nxt(n + 1);
	int j = 0;
	for (int i = 0; i <= n; i++) {
		while (j < n && h[j] < i)
			j++;
		nxt[i] = j;
	}
	vector<pi> dp(n + 1);
	vector<int> mem(n + 1);
	auto trial = [&](lint x) {
		int z = n;
		cht.clear();
		for (int i = n - 1; i >= 0; i--) {
			int ptr = max(i, nxt[i]);
			while (z > ptr) {
				cht.add_line(-2 * z, dp[z][0] + 2 * sum[z], 1 + dp[z][1]);
				z--;
			}
			dp[i] = pi{lint(1e18), 0};
			dp[i] = min(dp[i], cht.query(i));
			dp[i][0] -= 2 * sum[ptr];
			dp[i][0] += 2ll * ptr * i + x;
			dp[i] = min(dp[i], {dp[ptr][0] + x, dp[ptr][1] + 1});
		}
		return dp[0];
	};
	{
		lint s = 0, e = 1e12;
		while (s != e) {
			lint m = (s + e) / 2;
			if (trial(2 * m + 1)[1] > k)
				s = m + 1;
			else
				e = m;
		}
		cout << (trial(2 * s)[0] - k * (2 * s)) / 2 << endl;
	}
}