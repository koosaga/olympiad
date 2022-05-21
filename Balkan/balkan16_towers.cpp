#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 30005;
const int mod = 1e9 + 7;

lint mul(lint x, lint y, lint mod){ return (__int128) x * y % mod; }

lint ipow(lint x, lint y, lint p){
	lint ret = 1, piv = x % p;
	while(y){
		if(y&1) ret = mul(ret, piv, p);
		piv = mul(piv, piv, p);
		y >>= 1;
	}
	return ret;
}

namespace factors{
	bool miller_rabin(lint x, lint a){
		if(x % a == 0) return 0;
		lint d = x - 1;
		while(1){
			lint tmp = ipow(a, d, x);
			if(d&1) return (tmp != 1 && tmp != x-1);
			else if(tmp == x-1) return 0;
			d >>= 1;
		}
	}
	bool isprime(lint x){
		for(auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
			if(x == i) return 1;
			if(x > 40 && miller_rabin(x, i)) return 0;
		}
		if(x <= 40) return 0;
		return 1;
	}
	lint f(lint x, lint n, lint c){
		return (c + mul(x, x, n)) % n;
	}
	void rec(lint n, vector<lint> &v){
		if(n == 1) return;
		if(n % 2 == 0){
			v.push_back(2);
			rec(n/2, v);
			return;
		}
		if(isprime(n)){
			v.push_back(n);
			return;
		}
		lint a, b, c;
		while(1){
			a = rand() % (n-2) + 2;
			b = a;
			c = rand() % 20 + 1;
			do{
				a = f(a, n, c);
				b = f(f(b, n, c), n, c);
			}while(gcd(abs(a-b), n) == 1);
			if(a != b) break;
		}
		lint x = gcd(abs(a-b), n);
		rec(x, v);
		rec(n/x, v);
	}
	vector<lint> factorize(lint n){
		vector<lint> ret;
		rec(n, ret);
		sort(ret.begin(), ret.end());
		return ret;
	}
	lint euler_phi(lint n){
		auto pf = factorize(n);
		pf.resize(unique(all(pf)) - pf.begin());
		for(auto &p : pf){
			n -= n / p;
		}
		return n;
	}
};

// a[0]^(a[1]^(a[2]^...)) mod positive integer. assumes all a[i] > 0
lint tetration(vector<lint> a, lint mod) {
	if(sz(a) > 128) a.resize(128); // 2 * log(maxA)
	vector<lint> mod_chain = {mod};
	while(mod_chain.back() > 1){
		lint newVal = factors::euler_phi(mod_chain.back());
		mod_chain.push_back(newVal);
	}
	int nsz = min(sz(a), sz(mod_chain));
	a.resize(nsz);
	mod_chain.resize(nsz);
	lint v = 1;
	auto ipow = [&](lint x, lint n, lint mod) -> lint {
		if (x >= mod) x = x % mod + mod;
		lint v = 1;
		do {
			if (n & 1) {
				v *= x;
				if (v >= mod) v = v % mod + mod;
			}
			x *= x;
			if (x >= mod) x = x % mod + mod;
			n /= 2;
		} while (n);
		return v;
	};

	for(int i = sz(a) - 1; i >= 0; i--){
		v = ipow(a[i], v, mod_chain[i]);
	}
	return v % mod;
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t, m; cin >> t >> m;
	for(int i = 0; i < t; i++){
		int n; cin >> n;
		vector<lint> a(n);
		for(auto &i : a) cin >> i;
		cout << tetration(a, m) << "\n";
	}

}

