#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	auto b = a;
	for (int i = 1; i < n; i++)
		a[i] = max(a[i], a[i - 1] - k);
	for (int i = n - 2; i >= 0; i--)
		a[i] = max(a[i], a[i + 1] - k);
	cout << accumulate(all(a), 0ll) - accumulate(all(b), 0ll) << "\n";
}