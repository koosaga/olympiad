#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	lint sum = accumulate(all(a), 0ll);
	lint ans = 0;
	for (int i = 0; i < n; i++) {
		lint curH = sum / n + (n - sum % n <= i);
		ans += max(curH - a[i], 0ll);
	}
	cout << ans << "\n";
}