#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<pi> a(n);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < n; j++)
			cin >> a[j][i];
	vector<int> ans(n);
	vector<int> ban(n);
	for (int i = 0; i < n; i++) {
		if (a[i][0] < a[i][1])
			ans[i] = ban[i] = 1;
	}
	int c = count(all(ans), 1);
	bool flip = false;
	if (c > k) {
		flip = true;
		for (int i = 0; i < n; i++) {
			swap(a[i][0], a[i][1]);
			ban[i] = 1 - ban[i];
			ans[i] = 1 - ans[i];
		}
		c = n - c;
		k = n - k;
	}
	vector<pi> trace;
	auto trial = [&](lint t) {
		int n = sz(a);
		trace.clear();
		set<pi> st;
		lint L = 0, R = 0;
		int zers = 0;
		for (int i = 0; i < n; i++) {
			L += min(a[i][1], a[i][0]);
			R += a[i][0];
			if (!ban[i]) {
				st.insert(pi{a[i][0] - min(a[i][1], a[i][0]), i});
			}
			if (L > t)
				return -1;
			while (R > t) {
				R -= (*st.rbegin())[0];
				st.erase(--st.end());
			}
			while (L < 0 && sz(st)) {
				if (L + (*st.begin())[0] <= 0) {
					auto q = *st.begin();
					L += q[0];
					trace.push_back({0, q[1]});
					st.erase(st.begin());
					zers++;
				} else {
					auto q = *st.begin();
					st.erase(st.begin());
					st.insert(pi{q[0] + L, q[1]});
					L = 0;
				}
			}
			if (L < 0)
				L = R = 0;
		}
		for (auto &[v, i] : st)
			trace.push_back({v, i});
		return zers + sz(st);
	};
	lint s = 0, e = 1e15;
	while (s != e) {
		lint m = (s + e) / 2;
		if (trial(m) >= k - c)
			e = m;
		else
			s = m + 1;
	}
	cout << s << "\n";
	trial(s);
	for (int i = 0; i < k - c; i++) {
		ans[trace[i][1]] = 1;
	}
	string dap(n, 'B');
	for (int i = 0; i < n; i++) {
		if (ans[i])
			dap[i] = 'A';
	}
	for (auto &s : dap) {
		if (flip)
			s = 'A' + 'B' - s;
	}
	cout << dap << "\n";
}