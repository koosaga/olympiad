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
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	reverse(all(a));
	int z = a[k - 1];
	while (k < n && a[k] == z)
		k++;
	cout << k << "\n";
}