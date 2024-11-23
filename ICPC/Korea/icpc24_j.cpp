#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int l, n;
	cin >> l >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	auto trial = [&](int x) {
		vector<int> p(n), s(n);
		for (int i = 0; i < n; i++) {
			if (i > 0 && p[i - 1] < a[i]) {
				if (p[i - 1] < a[i] - x)
					p[i] = -1e9;
				else
					p[i] = a[i] + x - (a[i] - p[i - 1]) * 2;
			} else {
				p[i] = a[i] + x;
			}
		}
		for (int i = n - 1; i >= 0; i--) {
			if (i < n - 1 && s[i + 1] > a[i]) {
				if (s[i + 1] > a[i] + x) {
					s[i] = 1e9;
				} else {
					s[i] = a[i] - x + (s[i + 1] - a[i]) * 2;
				}
			} else
				s[i] = a[i] - x;
		}
		for (int i = 1; i < n; i++) {
			if (p[i - 1] >= s[i])
				return true;
		}
		return false;
	};
	lint s = 0, e = l;
	while (s != e) {
		lint m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m + 1;
	}
	cout << s << "\n";
}