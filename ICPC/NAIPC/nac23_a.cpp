#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using ll = long long;
using pll = pair<ll, ll>;

int n, d;
int main() {
	int TC;
	scanf("%d", &TC);
	while (TC--) {
		ll n, d;
		scanf("%lld%lld", &n, &d);
		ll t = 1;
		int c = 0;
		while (t < n) {
			if (n / (d + 1) < t) {
				c++;
				break;
			}
			t *= d + 1;
			c++;
		}
		printf("%d\n", c);
	}
}