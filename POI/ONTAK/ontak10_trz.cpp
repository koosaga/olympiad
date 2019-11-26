#include <bits/stdc++.h>
using namespace std;
const int MAXN = 16;
using ll = long long;

// number of (x, y) : (0 <= x < n && 0 < y <= k/d x + b/d)
// argument should be positive
ll count_solve(ll n, ll k, ll b, ll d) {
	if (k == 0) {
		return (b / d) * n;
	}
	if (k >= d || b >= d) {
		return ((k / d) * (n - 1) + 2 * (b / d)) * n / 2 + count_solve(n, k % d, b % d, d);
	}
	return count_solve((k * n + b) / d, d, (k * n + b) % d, k);
}

int main(){
	ll a, b, c; cin >> a >> b >> c;
	cout << count_solve(c / a + 1, a, b + c % a, b) << endl;
}

