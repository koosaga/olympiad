#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> a(2 * n + 1), b(2 * n + 1);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	for (int i = 1; i <= n; i++) {
		a[i + n - 1] = a[i - 1];
		b[i + n] = b[i];
	}
	lint dap = 1e18;
	for (int i = 1; i <= 2 * n; i++)
		b[i] += b[i - 1];
	priority_queue<pi> pq;
	for (int i = 0; i < n; i++)
		pq.push({a[i] - b[i], i});
	for (int i = 0; i < n; i++) {
		while (pq.top()[1] < i)
			pq.pop();
		lint ans = pq.top()[0] + b[i];
		pq.push({a[i + n] - b[i + n], i + n});
		dap = min(dap, ans);
	}
	cout << dap << "\n";
}