// need factorization
// https://judge.yosupo.jp/submission/74042

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

