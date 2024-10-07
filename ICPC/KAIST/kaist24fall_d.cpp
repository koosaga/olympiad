#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	lint v = 1e17;
	int l = 2 * n + 1, r = n + 1;
	for (int i = 0; i < n + 2; i++) {
		cout << v << " ";
		if (i % 2 == 0)
			v += l--;
		else
			v -= r++;
	}
}