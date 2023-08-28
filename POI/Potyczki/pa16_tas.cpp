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
	int n, t;
	cin >> n >> t;
	vector<int> a(1 << n);
	for (auto &x : a)
		cin >> x;
	if (t & 1)
		reverse(all(a));
	for (auto &x : a)
		cout << x << " ";
}