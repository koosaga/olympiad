#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

pair<bool, vector<pi>> solve(vector<int> a) {
	vector<pi> v;
	auto reps = [&](int pos, int cnt) {
		pos++; // 1-based
		assert(cnt >= 2);
		while (cnt > 3) {
			v.push_back({pos, 2});
			cnt -= 2;
		}
		v.push_back({pos, cnt});
	};
	int n = sz(a);
	assert(n % 2 == 1);
	int lo = n / 2, hi = n / 2;
	while (lo >= 0 && a[lo] == 1)
		lo--;
	while (hi < n && a[hi] == 1)
		hi++;
	if (lo < 0 || hi >= n || hi - lo > n / 2)
		return make_pair(false, vector<pi>());
	if (lo == n / 2) {
		int sum = accumulate(a.begin(), a.begin() + n / 2 + 1, 0);
		for (int i = n / 2; i >= 0; i--) {
			sum -= a[i];
			reps(sum, a[i] + (i < n / 2 ? a[n - 1 - i] : 0));
		}

		return make_pair(true, v);
	}
	int sum = accumulate(a.begin(), a.begin() + hi + 1, 0);
	int iter = (n - 2 * lo - 1) / 2;
	for (int i = 0; i < iter; i++) {
		assert(hi + i + 1 < sz(a));
		sum -= a[hi - i];
		reps(sum, a[hi - i] + (i > 0 ? a[hi + i] : 0));
	}
	a.erase(a.begin() + hi - iter + 1, a.begin() + hi + 1 + iter - 1);
	a[hi - iter] += a[hi - iter + 1];
	a.erase(a.begin() + hi - iter + 1);
	n = sz(a);
	assert(a[n / 2] > 1);
	sum = accumulate(a.begin(), a.begin() + n / 2 + 1, 0);
	for (int i = n / 2; i >= 0; i--) {
		sum -= a[i];
		reps(sum, a[i] + (i < n / 2 ? a[n - 1 - i] : 0));
	}
	return make_pair(true, v);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	vector<int> a;
	{
		int n;
		cin >> n;
		string s;
		cin >> s;
		for (int i = 0; i < sz(s);) {
			int j = i;
			while (j < sz(s) && s[i] == s[j])
				j++;
			a.push_back(j - i);
			i = j;
		}
	}
	if (sz(a) % 2 == 0) {
		vector<int> clzL(sz(a), -1);
		vector<int> clzR(sz(a), sz(a));
		int clz = -1;
		for (int i = 0; i < sz(a); i++) {
			if (a[i] > 1)
				clz = i;
			clzL[i] = clz;
		}
		clz = sz(a);
		for (int i = sz(a) - 1; i >= 0; i--) {
			if (a[i] > 1)
				clz = i;
			clzR[i] = clz;
		}
		for (int i = 1; i < sz(a); i += 2) {
			int ll = clzL[i / 2], lr = clzR[i / 2];
			int rl = clzL[(sz(a) + i) / 2], rr = clzR[(sz(a) + i) / 2];
			if (lr >= i || ll < 0 || lr - ll > i / 2)
				continue;
			if (rr >= sz(a) || rl < i || rr - rl > (sz(a) - i) / 2)
				continue;
			vector<int> b(a.begin(), a.begin() + i);
			vector<int> c(a.begin() + i, a.end());
			auto [p1, a1] = solve(b);
			auto [p2, a2] = solve(c);
			assert(p1 && p2);
			cout << sz(a1) + sz(a2) << "\n";
			for (auto [x, y] : a1)
				cout << x << " " << y << "\n";
			for (auto [x, y] : a2)
				cout << x << " " << y << "\n";
			return 0;
		}
		cout << "-1\n";
		return 0;
	}
	auto [p, z] = solve(a);
	if (p) {
		cout << sz(z) << "\n";
		for (auto [x, y] : z)
			cout << x << " " << y << "\n";
	} else
		cout << "-1\n";
}