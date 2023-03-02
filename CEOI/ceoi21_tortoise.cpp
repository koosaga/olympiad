#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n), l(n), r(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	{
		int clz = -1e9;
		for (int i = 0; i < n; i++) {
			if (a[i] == -1)
				clz = i;
			l[i] = i - clz;
		}
	}
	{
		int clz = 1e9;
		for (int i = n - 1; i >= 0; i--) {
			if (a[i] == -1)
				clz = i;
			r[i] = clz - i;
		}
	}
	vector<int> rUp(n);
	{
		int clz = 1e9;
		for (int i = n - 1; i >= 0; i--) {
			rUp[i] = clz;
			if (a[i] > 0)
				clz = i;
		}
	}
	lint ans = 0;
	priority_queue<pi> slopes;
	lint sum = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] <= 0)
			continue;
		int right = 1e9;
		if (rUp[i] < n) {
			right = max(0, i + r[i] - rUp[i]);
		}
		auto insert = [&](int z, int c) {
			if (c == 0)
				return;
			slopes.push({z, c});
			cnt += c;
			sum += 1ll * z * c;
		};
		insert(2 * min({l[i], r[i], right}), 1);
		insert(2 * min(l[i], r[i]), a[i] - 1);
		int thres = i + 2 * min({l[i], r[i], right});
		while (sum > thres) {
			auto z = slopes.top();
			slopes.pop();
			lint toSat = min(z[1], (sum - thres + z[0] - 1) / z[0]);
			sum -= toSat * z[0];
			cnt -= toSat;
			z[1] -= toSat;
			if (z[1] > 0)
				slopes.push(z);
		}
		ans = max(ans, cnt);
	}
	ans = -ans;
	for (auto &x : a) {
		if (x > 0)
			ans += x;
	}
	cout << ans << "\n";
}