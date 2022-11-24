#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, t, b;
	cin >> n >> b >> t;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	vector<lint> s1(n + 1), s2(n + 1);
	for (int i = 1; i <= n; i++) {
		s1[i] = s1[i - 1] + a[i - 1];
		s2[i] = s2[i - 1] + a[i - 1] / 2;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		lint sum = s1[max(i - t, 0)] + s2[i] - s2[max(i - t, 0)];
		if (sum <= b)
			ans = i;
	}
	cout << ans << "\n";
}