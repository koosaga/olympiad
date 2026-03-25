#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<array<lint, 3>> a(n * 2);
	for (int i = 0; i < n; i++) {
		lint x, y;
		cin >> x >> y;
		a[2 * i] = array<lint, 3>{y, 1, i};
		a[2 * i + 1] = array<lint, 3>{y + x, -1, i};
	}
	sort(all(a));
	set<int> s;
	for (int i = 1; i <= n; i++)
		s.insert(i);
	vector<int> color(n);
	for (int i = 0; i < 2 * n; i++) {
		if (a[i][1] == 1) {
			color[a[i][2]] = *s.begin();
			s.erase(s.begin());
		} else {
			s.insert(color[a[i][2]]);
		}
	}
	cout << *max_element(all(color)) << "\n";
	vector<int> ord(n);
	iota(all(ord), 0);
	sort(all(ord), [&](int a, int b) { return color[a] < color[b]; });
	for (auto &x : ord)
		cout << x + 1 << "\n";
}