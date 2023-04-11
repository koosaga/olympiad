#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

lint f(lint a, lint b) {
	if (a == b)
		return 2 * a - 1;
	if (a < b) {
		return f(a, b - ((b - 1) / a) * a) + (b - 1) / a;
	}
	if (a > 2 * b) {
		return f(a - ((a - 1) / b - 1) * b, b) + ((a - 1) / b - 1);
	}
	return f(a - b, b) + (a - 1) / (a - b);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint t;
	cin >> t;
	while (t--) {
		lint a, b;
		cin >> a >> b;
		cout << f(a, b) << "\n";
	}
}