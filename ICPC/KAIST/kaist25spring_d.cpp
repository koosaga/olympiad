#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int bitrev(int x, int k) {
	int y = 0;
	for (int i = 0; i < k; i++) {
		if ((x >> i) & 1)
			y |= (1 << (k - i - 1));
	}
	return y;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	if (n != (n & -n)) {
		cout << "0\n";
		return 0;
	}
	cout << "1\n";
	int l = 0;
	while ((2 << l) <= n)
		l++;
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			cout << bitrev(j ^ k, l) + 1 << " ";
		}
		cout << "\n";
	}
}