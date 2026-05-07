#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> m >> n;
	vector<pi> a(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	vector<pi> b(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i][0];
		b[i][1] = i;
	}
	sort(all(b));
	for (int i = 0; i < m; i++) {
		a[i][0] = lower_bound(all(b), pi{a[i][0], int(2e9)}) - b.begin();
	}
	sort(all(a));
	auto trial = [&](int t) {
		vector<int> cnt(n);
		for (int i = 0; i < n; i++) {
			if (b[i][1] < t)
				cnt[i]++;
		}
		for (int i = 0; i < m; i++) {
			if (a[i][0])
				cnt[a[i][0] - 1]--;
		}
		int sum = 0;
		for (int i = n - 1; i >= 0; i--) {
			sum += cnt[i];
			if (sum > 0)
				return false;
		}
		return true;
	};
	int s = 0, e = n;
	while (s != e) {
		int m = (s + e + 1) / 2;
		if (trial(m))
			s = m;
		else
			e = m - 1;
	}
	cout << s;
	int j = m;
	priority_queue<int> pq;
	lint sum = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (b[i][1] >= s)
			continue;
		while (j > 0 && a[j - 1][0] > i) {
			pq.push(a[--j][1]);
		}
		assert(sz(pq));
		sum += pq.top();
		pq.pop();
	}
	cout << " " << sum << "\n";
}