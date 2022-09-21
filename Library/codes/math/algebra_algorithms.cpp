using pol = poly<mint>;

mint resultant(pol &a, pol &b){
    if(a.deg() == -1 || b.deg() == -1) return 0;
    if(a.deg() == 0 || b.deg() == 0){
        return ipow(a.lead(), b.deg()) * ipow(b.lead(), a.deg());
    }
    if(b.deg() > a.deg()){
        mint flag = (a.deg() % 2 && b.deg() % 2) ? -1 : 1;
        return resultant(b, a) * flag;
    }
    poly nxt = a % b;
    return ipow(b.lead(), a.deg() - nxt.deg()) * resultant(nxt, b);
}

pol interpolate(vector<mint> y, vector<mint> x){
    int n = sz(y);
    vector<mint> res(n), temp(n);
    for(int k = 0; k < n-1; k++){
        for(int i = k+1; i < n; i++){
            y[i] = (y[i] - y[k]) / (x[i] - x[k]);
        }
    }
    mint last = 0; temp[0] = 1;
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            res[i] += y[k] * temp[i];
            swap(last, temp[i]);
            temp[i] -= last * x[k];
        }
    }
    return res;
}

pol interpolate_x0toxn(vector<mint> y){
    int n = sz(y);
    vector<mint> res(n), temp(n);
    vector<mint> x;
    for(int i = 0; i < n; i++){
        x.push_back(mint(1) / mint(i + 1));
    }
    for(int k = 0; k < n-1; k++){
        for(int i = k+1; i < n; i++){
            y[i] = (y[i] - y[k]) * x[i - k - 1];
        }
    }
    mint last = 0; temp[0] = 1;
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            res[i] += y[k] * temp[i];
            swap(last, temp[i]);
            temp[i] -= last * mint(k);
        }
    }
    return res;
}

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
