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
	int n, m;
	cin >> n >> m;
	vector<int> cnt(m + 1);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	auto f = [&](int i) {
		cnt[1] += i;
		cnt[m] += cnt[0] - i;
		lint sum = 0, ans = 0;
		for (int i = 1; i < m; i++) {
			sum += cnt[i];
			ans += 1ll * sum * (n - sum);
		}
		cnt[1] -= i;
		cnt[m] -= cnt[0] - i;
		return ans;
	};
	int s = 0, e = cnt[0];
	while (s != e) {
		int m = (s + e) / 2;
		if (f(m) < f(m + 1))
			s = m + 1;
		else
			e = m;
	}
	cout << f(s) << "\n";
}