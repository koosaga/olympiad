#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 300005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i][0] >> a[i][1];
	int ans = 0;
	for (int i = 0; i < n;) {
		int cur = a[i][0];
		while (i < n) {
			if (cur < a[i][0])
				cur = a[i][0];
			else if (cur > a[i][1]) {
				break;
			}
			i++;
		}
		ans++;
	}
	cout << ans << "\n";
}