#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	/*
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);*/
	int n;
	cin >> n;
	vector<int> perm(n);
	iota(all(perm), 1);
	shuffle(all(perm), mt19937(0x1557));

	auto query = [&](int x, int y) {
		cout << "? " << perm[x] << " " << perm[y] << endl;
		int z = min(perm[x], perm[y]);
		cin >> z;
		return z;
	};
	int i1 = 0, i2 = 1, mx = query(0, 1);
	vector<int> ans(n);
	ans[0] = ans[1] = mx;
	int fucked = 0;
	for (int i = 2; i < n; i++) {
		int z = query(i1, i);
		if (z < mx) {
			ans[i] = z;
			continue;
		}
		if (z > mx) {
			ans[i1] = ans[i] = z;
			mx = z;
			i2 = i;
			continue;
		}
		if (z == mx) {
			fucked++;
			int w = query(i2, i);
			mx = w;
			ans[i] = ans[i2] = w;
			i1 = i;
		}
	}
	cout << "!";
	for (int i = 1; i <= n; i++) {
		int pos = find(all(perm), i) - perm.begin();
		cout << " " << ans[pos];
	}
	cout << endl;
}