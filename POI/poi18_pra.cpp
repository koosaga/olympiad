#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<array<int, 3>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
		a[i][2] = i;
	}
	sort(all(a));
	array<int, 3> ans = {0, 0, 0};
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < n; i++) {
		pq.push(a[i][1]);
		while (sz(pq) > k)
			pq.pop();
		if (sz(pq) == k && a[i][0] < pq.top()) {
			ans = max(ans, {pq.top() - a[i][0], a[i][0], pq.top()});
		}
	}
	cout << ans[0] << "\n";
	vector<int> vect;
	for (int i = 0; i < n; i++) {
		if (a[i][0] <= ans[1] && ans[2] <= a[i][1])
			vect.push_back(a[i][2]);
	}
	sort(all(vect));
	vect.resize(k);
	for (auto &x : vect)
		cout << x + 1 << " ";
}