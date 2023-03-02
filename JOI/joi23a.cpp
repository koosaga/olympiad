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
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<array<int, 3>> stk;
	multiset<int> exists;
	for (int i = 0; i < n; i++) {
		if (!exists.count(a[i])) {
			stk.push_back({i, i, a[i]});
			exists.insert(a[i]);
		} else {
			while (sz(stk) && stk.back()[2] != a[i]) {
				exists.erase(exists.find(stk.back()[2]));
				stk.pop_back();
			}
			array<int, 3> toput = {0, i, a[i]};
			if (sz(stk))
				toput[0] = stk.back()[1] + 1;
			exists.insert(a[i]);
			stk.push_back(toput);
		}
	}
	for (auto &x : stk) {
		for (int y = 0; y < x[1] - x[0] + 1; y++)
			cout << x[2] << "\n";
	}
}
