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
int main() {
	ll a;
	scanf("%lld", &a);
	if (a == 1) {
		printf("1\n");
		return 0;
	}
	for (int i = 60; i >= 2; i--) {
		ll x = (ll)(pow(a, 1.0 / i) + 0.5);
		ll z = a;
		// printf("%lld\n", x);
		int ck = 0;
		for (int j = 0; j < i; j++) {
			if (z % x) {
				ck = 1;
				break;
			}
			z /= x;
		}
		if (z == 1 && !ck) {
			int c = 0;
			for (ll j = 1; j * j <= x; j++) {
				if (x % j == 0) {
					if (j * j == x)
						c++;
					else
						c += 2;
				}
			}
			if (c == i) {
				printf("%lld\n", x);
				return 0;
			}
		}
	}
	puts("-1");
}