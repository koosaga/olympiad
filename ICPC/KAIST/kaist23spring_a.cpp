#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, a, b;
	cin >> n >> a >> b;
	if (gcd(a, b) > 1) {
		cout << "No\n";
		return 0;
	}
	cout << "Yes\n";
	for (int i = 0; i < n * 2; i += 2) {
		cout << a + i * b << " " << a + i * b + b << "\n";
	}
}