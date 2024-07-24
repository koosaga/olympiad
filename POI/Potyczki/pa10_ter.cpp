#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<lint> game(vector<lint> v) {
	vector<lint> stk;
	for (auto &x : v) {
		while (sz(stk) >= 2 && stk[sz(stk) - 2] <= stk.back() && stk.back() >= x) {
			x += stk[sz(stk) - 2] - stk.back();
			stk.pop_back();
			stk.pop_back();
		}
		stk.push_back(x);
	}
	return stk;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	a.push_back(-1e18);
	int j = 0;
	if (a[0]) {
		while (a[j])
			j++;
		for (int k = 0; k < j; k++)
			a.push_back(a[k]);
	}
	lint sum = 0;
	vector<lint> stk;
	for (int i = j; i <= n;) {
		if (a[i] == 0) {
			i++;
			continue;
		}
		int j = i;
		while (j < sz(a) && a[j])
			j++;
		vector<lint> L;
		for (int k = i; k < j; k++) {
			L.push_back(a[k]);
		}
		sum += accumulate(all(L), 0ll);
		auto g = game(L);
		for (auto &x : g)
			stk.push_back(x);
		i = j;
	}
	sort(all(stk));
	reverse(all(stk));
	lint ans = 0;
	for (int i = 0; i < sz(stk); i++) {
		if (i % 2 == 0)
			ans += stk[i];
		else
			ans -= stk[i];
	}
	lint a1 = (sum + ans) / 2;
	lint a2 = (sum - ans) / 2;
	{
		if (a1 < -lint(1e16))
			a1 += lint(1e18);
		if (a2 < -lint(1e16))
			a2 += lint(1e18);
	}
	cout << a1 << " " << a2 << "\n";
}