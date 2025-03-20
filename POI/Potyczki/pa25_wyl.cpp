#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

bool cycle(vector<int> a) {
	int n = sz(a);
	for (int i = 0; i + 1 < n; i++) {
		if (a[i] <= 0)
			return false;
		a[i + 1] -= a[i];
	}
	return a[n - 1] == 0;
}
bool solve(vector<int> a) {
	auto input = a;
	int n = sz(a);
	for (int i = 0; i + 1 < n; i++) {
		a[i + 1] -= a[i];
	}
	auto ok = [&](vector<int> &a) {
		if (a[n - 1])
			return false;
		if (n > 1 && *min_element(all(a) - 1) <= 0)
			return false;
		return true;
	};
	if (ok(a))
		return true;
	vector<int> onetry = {n - 1, n - 2};
	for (int i = 0; i + 1 < n; i++) {
		if (a[i] <= 0 && i > 0) {
			onetry.push_back(i - 1);
			break;
		}
	}
	for (auto &x : onetry) {
		if (x >= 0) {
			auto b = input;
			b[x]--;
			if (cycle(b))
				return true;
		}
	}
	for (int i = 1; i < n && i < 3; i++) {
		auto b = input;
		for (int j = i; j + 1 < n; j++) {
			b[j]++;
			if (j >= n - 3 && cycle(b))
				return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (auto &x : a)
			cin >> x;
		int l = 0, r = n;
		while (l < r && a[l] == 0)
			l++;
		while (l < r && a[r - 1] == 0)
			r--;
		a.erase(a.begin(), a.begin() + l);
		a.resize(r - l);
		if (sz(a) == 0) {
			cout << "TAK\n";
			continue;
		}
		if (count(all(a), 0) > 0) {
			cout << "NIE\n";
			continue;
		}
		cout << (solve(a) ? "TAK" : "NIE") << "\n";
	}
}