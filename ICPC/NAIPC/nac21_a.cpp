#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	vector<lint> ans(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		a[i][1] = i;
		ans[i] = a[i][0];
	}
	sort(all(a));
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < n;) {
			int k = j;
			int hi = 0;
			while (k < n && (a[j][0] >> (i + 1)) == (a[k][0] >> (i + 1))) {
				if ((a[k][0] >> i) & 1)
					hi++;
				k++;
			}
			int p = j;
			for (int l = k - hi; l < k; l++) {
				while (a[p][0] < a[l][0] - (1ll << i))
					p++;
				swap(ans[a[p][1]], ans[a[l][1]]);
			}
			j = k;
		}
	}
	for (int i = 0; i < n; i++)
		cout << ans[i] << "\n";
}