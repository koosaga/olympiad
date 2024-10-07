#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, k, x;
	cin >> n >> k >> x;
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	auto trial = [&](int score) {
		vector<lint> v;
		for (auto &[x, y] : a) {
			v.push_back(1ll * max(x - score, 0) * y);
		}
		sort(all(v));
		return accumulate(v.begin(), v.begin() + n + 1 - x, 0ll) < k;
	};
	int s = 0, e = 1e6;
	while (s != e) {
		int m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m + 1;
	}
	cout << s << "\n";
}