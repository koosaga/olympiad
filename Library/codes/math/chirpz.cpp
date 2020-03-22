using pol = poly<mint>;
vector<mint> chirpz_even(pol p, mint x, int n){
	if(p.deg() == -1){
		return vector<mint>(n, 0);
	}
	vector<mint> sq_list(p.deg() + 1 + n);
	{
		mint cur = x;
		sq_list[0] = 1;
		for(int i=1; i<sz(sq_list); i++){
			sq_list[i] = cur * sq_list[i - 1];
			cur *= x * x;
		}
	}
	for(int i=0; i<=p.deg(); i++){
		p.a[i] /= sq_list[i];
	}
	p = p.reversed();
	poly q(sq_list);
	poly ret = p * q;
	vector<mint> ans(n);
	for(int i=0; i<n; i++){
		ans[i] = ret[i + p.deg()] / sq_list[i];
	}
	return ans;
}

vector<mint> chirpz(pol p, mint x, int n){  // return first n terms of p(x^{2k})
	pol poly_ev = p;
	pol poly_od = p;
	mint cur = 1;
	for(int i=0; i<=p.deg(); i++){
		poly_od.a[i] *= cur;
		cur *= x;
	}
	auto rx = chirpz_even(poly_ev, x, (n + 2) / 2);
	auto ry = chirpz_even(poly_od, x, (n + 1) / 2);
	vector<mint> ret;
	for(int i=0; i<sz(rx) || i<sz(ry); i++){
		if(i < sz(rx)) ret.push_back(rx[i]);
		if(i < sz(ry)) ret.push_back(ry[i]);
	}
	return ret;
}
