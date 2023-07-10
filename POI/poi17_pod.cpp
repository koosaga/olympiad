#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<lint> a(n);
	lint sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i] * i;
		sum %= (n - 1);
	}
	if (sum)
		a[sum]--;
	if (accumulate(a.begin() + 1, a.end(), 0ll) == 0) {
		a[0] = 1;
	}
	for (int i = 1; i < n; i++)
		a[i] += a[i - 1];
	while (q--) {
		lint x;
		cin >> x;
		if (a[n - 1] <= x) {
			cout << "-1\n";
			continue;
		}
		int l = upper_bound(a.begin(), a.end(), x) - a.begin();
		cout << l << "\n";
	}
}