#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 5005;

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

	lint mul(lint x, lint y, lint m){
		lint ret = 0;
		while(y){
			ret = (ret + x * (y & 1023)) % m;
			x = (x << 10) % m;
			y >>= 10;
		}
		return ret;
	}

	// Chinese remainder theorem: find z such that
	// z % m1 = r1, z % m2 = r2.  Here, z is unique modulo M = lcm(m1, m2).
	// Return (z, M).  On failure, M = -1.
	pair<lint, lint> CRT(lint m1, lint r1, lint m2, lint r2) {
		lint s, t;
		lint g = ext_gcd(m1, m2, s, t);
		if (r1%g != r2%g) return make_pair(0, -1);
		s = mul(s, r2, m2);
		t = mul(t, r1, m1);
		return make_pair(mod(s*(m1/g) + t*(m2/g), m1*(m2/g)), m1*(m2/g));
	}
}

namespace FIO{
static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
	if (!bytes || idx == bytes) {
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt() {
	int x = 0, s = 1;
	int c = _read();
	while (c <= 32) c = _read();
	if (c == '-') s = -1, c = _read();
	while (c > 32) x = 10 * x + (c - '0'), c = _read();
	if (s < 0) x = -x;
	return x;
}
}

int p[MAXN]; // next position
int stn[MAXN]; // starting number
int grp[MAXN], clen[MAXN], idx[MAXN];

int main(){
	while(true){
		int n;
		n = FIO::_readInt();
		if(n == 0) break;
		vector<int> ord;
		for(int i=0; i<n; i++){
			ord.push_back(2 * i + 1);
			ord.push_back(2 * i + 2);
			ord.push_back(2 * n + 2 * i + 1);
			ord.push_back(2 * n + 2 * i + 2);
			ord.push_back(4 * n + i + 1);
		}
		for(int i=0; i<ord.size(); i++) p[ord[i]] = i + 1;
		for(int i=0; i<5*n; i++){
			int x = FIO::_readInt();
			stn[x] = i + 1;
		}
		for(int i=1; i<=5*n; i++) grp[i] = clen[i] = 0;
		int piv = 0;
		for(int i=1; i<=5*n; i++){
			if(!grp[i]){
				int l = 0;
				piv++;
				for(int j=i; !grp[j]; j=p[j]){
					grp[j] = piv;
					idx[j] = ++l;
				}
				for(int j=i; !clen[j]; j=p[j]){
					clen[j] = l;
				}
			}
		}
		pi ret((1ll << 63) - 1, 1e9);
        vector<pi> eq;
		for(int i=0; i<n; i++){
			vector<int> w(5);
			iota(w.begin(), w.end(), 5 * i + 1);
			vector<int> v = {1, 2, 3, 4, 5};
			for(auto &i : v) i = stn[i];
			sort(v.begin(), v.end());
			do{
                eq.clear();
				for(int j=0; j<5; j++){
					if(grp[v[j]] != grp[w[j]]){
						break;
					}
					int PERIOD = clen[v[j]];
					int REP = idx[w[j]] - idx[v[j]] + PERIOD;
                    while(REP >= PERIOD) REP -= PERIOD;
					eq.emplace_back(PERIOD, REP);
				}
				if(eq.size() != 5) continue;
				for(int i=1; i<eq.size(); i++){
					eq[0] = Euclid::CRT(eq[0].first, eq[0].second, eq[i].first, eq[i].second);
					if(eq[0].second == -1) break;
					swap(eq[0].first, eq[0].second);
				}
				if(eq[0].second == 0) eq[0].second = eq[0].first;
				if(eq[0].second != -1){
					ret = min(ret, pi(eq[0].second, i));
				}
			}while(next_permutation(v.begin(), v.end()));
		}
		if(ret.second > n) puts("Neverending game.");
		else printf("Player %lld wins game number %lld.\n", ret.second + 1, ret.first);
	}
}
