#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1000005;

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
		if (r1%g != r2%g) return make_pair(0, -1);
		s = mod(s * r2, m2);
		t = mod(t * r1, m1);
		return make_pair(mod(s*(m1/g) + t*(m2/g), m1*(m2/g)), m1*(m2/g));
	}
}

int mod;

struct line{
	lint a, b, c;
	line(){}
	line(pi x, pi y){
		a = (y.second - x.second + mod) % mod;
		b = (x.first - y.first + mod) % mod;
		c = (a * x.first + b * x.second) % mod;
	}
};

bool xopowo(line a, line b, pi &c){
	lint det = a.a * b.b - a.b * b.a;
	det = (det % mod + mod) % mod;
	if(det == 0) return 0;
	det = Euclid::mod_inverse(det, mod);
	c.first = (a.c * b.b - a.b * b.c) % mod + mod;
	c.second = (a.a * b.c - a.c * b.a) % mod + mod;
	c.first = c.first * det % mod;
	c.second = c.second * det % mod;
	return 1; 
}

int n;
pi d;
pi a[MAXN][3];

int main(){
	scanf("%d",&n);
	scanf("%d %d",&d.first,&d.second);
	for(int i=0; i<n; i++){
		for(int j=0; j<3; j++){
			scanf("%d %d",&a[i][j].first,&a[i][j].second);
		}
	}
	int dap = 0;
	for(auto &i : {int(1e9) + 409, int(1e9) + 433, int(1e9) + 696969}){
		mod = i;
		auto curd = d;
		for(int j=0; j<n; j++){
			// insec of (a[i], b[i]) and (c[i], d[i])
			// if infty or undef, kill
			line l1(a[j][0], a[j][1]);
			line l2(a[j][2], curd);
			if(!xopowo(l1, l2, curd)) break;
			else dap = max(dap, j + 1);
		}
	}
	cout << dap << endl;
}
