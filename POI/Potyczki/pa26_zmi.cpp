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
	int x;
	array<int, 3> a;
	cin >> x >> a[0] >> a[1] >> a[2];
	if (a[0] >= 29 && a[1] > 2)
		a[1]--;
	if (pi{x + 22, 12} > pi{a[0], a[1]}) {
		a[0] = x + 22;
		a[1] = 12;
		a[2] = 0;
	}
	auto gen = [&](int x) {
		if (x <= 4)
			return array<int, 3>{x + 24, 0, 0};
		else
			return array<int, 3>{29, 23, 0};
	};
	auto sub = [&](array<int, 3> a, array<int, 3> b) {
		return (b[0] - a[0]) * 1440 + (b[1] - a[1]) * 60 + b[2] - a[2];
	};
	cout << sub(a, gen(x)) << "\n";
}