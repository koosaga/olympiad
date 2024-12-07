#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x, x--;
	reverse(all(a));
	vector<int> l(n, -1), r(n, -1);
	lint ans = 0;
	for (int i = 1; i < n; i++) {
		int cur = a[i - 1];
		int prv = a[i];
		int lastLeft = a[i], lastRight = a[i];
		while (cur != -1) {
			if (cur < a[i] && prv >= a[i]) {
				l[lastRight] = -1;
				if (lastLeft != a[i]) {
					r[lastLeft] = cur;
				} else
					l[a[i]] = cur;
				ans++;
			} else if (cur > a[i] && prv <= a[i]) {
				r[lastLeft] = -1;
				if (lastRight != a[i]) {
					l[lastRight] = cur;
				} else
					r[a[i]] = cur;
				ans++;
			}
			if (cur < a[i])
				lastLeft = cur;
			else
				lastRight = cur;
			prv = cur;
			if (cur < a[i]) {
				cur = r[cur];
			} else {
				cur = l[cur];
			}
		}
		ans--;
	}
	cout << ans << "\n";
}