#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2505;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

namespace Euclid{
	lint gcd(lint x, lint y) { return y ? gcd(y, x%y) : x; }
	lint mod(lint a, lint b) { return ((a%b) + b) % b; }

	// returns g = gcd(a, b); finds x, y such that g = ax + by
	lint ext_gcd(lint a, lint b, lint &x, lint &y) {
		lint xx = y = 0;
		lint yy = x = 1;
		while (b) {
			lint q = a / b;
			lint t = b; b = a%b; a = t;
			t = xx; xx = x - q*xx; x = t;
			t = yy; yy = y - q*yy; y = t;
		}
		return a;
	}

	// computes b such that ab = 1 (mod n), returns -1 on failure
	lint mod_inverse(lint a, lint n) {
		lint x, y;
		lint g = ext_gcd(a, n, x, y);
		if (g > 1) return -1;
		return mod(x, n);
	}

	// Chinese remainder theorem: find z such that
	// z % m1 = r1, z % m2 = r2.  Here, z is unique modulo M = lcm(m1, m2).
	// Return (z, M).  On failure, M = -1.
	pair<lint, lint> CRT(lint m1, lint r1, lint m2, lint r2) {
		lint s, t;
		lint g = ext_gcd(m1, m2, s, t);
		if (r1%g != r2%g) return make_pair(-1, (1ll << 60));
		s = mod(s * r2, m2);
		t = mod(t * r1, m1);
		return make_pair(mod(s*(m1/g) + t*(m2/g), m1*(m2/g)), m1*(m2/g));
	}
}

lint solve(int r1, int r2, int a1, int a2, int m1, int m2){
	if(a1 < 0) a1 = -a1, r1 = -r1;
	if(a2 < 0) a2 = -a2, r2 = -r2;
	r1 = Euclid::mod(r1, m1);
	r2 = Euclid::mod(r2, m2);
	a1 %= m1;
	a2 %= m2;
	if(Euclid::gcd(a1, m1) != 1){
		int g = Euclid::gcd(a1, m1);
		if(r1 % g) return (1ll << 60);
		a1 /= g; m1 /= g, r1 /= g;
	}
	if(Euclid::gcd(a2, m2) != 1){
		int g = Euclid::gcd(a2, m2);
		if(r2 % g) return (1ll << 60);
		a2 /= g; m2 /= g, r2 /= g;
	}
	if(a1 == 0){
		swap(r1, r2);
		swap(a1, a2);
		swap(m1, m2);
	}
	if(a2 == 0){
		lint x = Euclid::mod_inverse(a1, m1);
		if(x < 0) return (1ll << 60);
		return x * r1 % m1;
	}
	lint v1 = Euclid::mod_inverse(a1, m1);
	lint v2 = Euclid::mod_inverse(a2, m2);
	if(v1 < 0 || v2 < 0) return (1ll << 60);
	v1 = (v1 * r1) % m1;
	v2 = (v2 * r2) % m2;
	auto ret = Euclid::CRT(m1, v1, m2, v2);
	if(ret.first == -1) return (1ll << 60);
	return ret.first;
	// a1 * T = r1 (mod m1) (a1, r1 < m1)
	// a2 * T = r2 (mod m2) (a2, r2 < m2)
}
int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		pi v[5];
		for(int i=0; i<5; i++) scanf("%lld %lld",&v[i].first,&v[i].second);
		lint ans[2] = {(1ll<<60), (1ll<<60)};
		int g = Euclid::gcd(abs(v[4].first), abs(v[4].second));
		v[4].first /= g;
		v[4].second /= g;
		for(int i=0; i<2; i++){
			for(auto &x : {v[i+2].first, 2 * v[0].first - v[i+2].first}){
				for(auto &y : {v[i+2].second, 2 * v[0].second - v[i+2].second}){
					ans[i] = min(ans[i], 
					solve(
					x - v[1].first, y - v[1].second, 
					v[4].first, v[4].second, 
					2 * v[0].first, 2 * v[0].second
					));
				}
			}
		}
		if(ans[0] < ans[1]) puts("A");
		if(ans[0] == ans[1]) puts("O");
		if(ans[0] > ans[1]) puts("B");
	}
}
