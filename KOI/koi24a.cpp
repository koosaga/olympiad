
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<int, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, k, l;
	cin >> l >> n >> k;
	vector<lint> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<lint> v;
	for (int i = 0; i + 1 < n; i++) {
		lint d = a[i + 1] - a[i];
		v.push_back(d / 2);
		v.push_back((d - 1) / 2);
	}
	if (a[0] > 0)
		v.push_back(a[0]);
	if (a[n - 1] < l)
		v.push_back(l - a[n - 1]);
	sort(all(v));
	for (int i = 0; i < min(k, n); i++) {
		cout << "0\n";
	}
	k -= min(k, n);
	if(k == 0) return 0;
	int j = 0;
	for (int i = 1;k; i++) {
		while (v[j] < i)
			j++;
		for (int x = j; x < sz(v); x++) {
			if (k == 0)
				break;
			k--;
			cout << i << "\n";
		}
	}
}