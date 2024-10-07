#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> l(n, -1), r(n, n);
	{
		vector<int> stk;
		for (int i = 0; i < n; i++) {
			while (sz(stk) && a[stk.back()] > a[i]) {
				stk.pop_back();
			}
			if (sz(stk))
				l[i] = stk.back();
			stk.push_back(i);
		}
	}
	{
		vector<int> stk;
		for (int i = n - 1; i >= 0; i--) {
			while (sz(stk) && a[stk.back()] >= a[i]) {
				stk.pop_back();
			}
			if (sz(stk))
				r[i] = stk.back();
			stk.push_back(i);
		}
	}
	for (int i = 0; i < n; i++) {
		int w = i;
		if (l[i] != -1 && r[i] != n) {
			w = (a[l[i]] <= a[r[i]] ? r[i] : l[i]);
		} else if (l[i] != -1)
			w = l[i];
		else if (r[i] != n)
			w = r[i];
		cout << w << " ";
	}
}