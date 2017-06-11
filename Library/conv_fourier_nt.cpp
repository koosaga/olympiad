namespace nt_fft{
	const int prr = 3;
	void fft(vector<int> &v, bool inv){
		vector<int> w(v.size());
		for(int i=2; i<=v.size(); i<<=1){
			int bsz = v.size() / i;
			int ang = ipow(prr, (mod - 1) / i);
			if(inv) ang = ipow(ang, mod-2);
			for(int j=0; j<bsz; j++){
				for(int k=0; k<i; k++){
					w[k] = v[j + k * bsz];
				}
				lint cur = 1;
				for(int k=0; k<i/2; k++){
					lint a = w[2*k], b = cur * w[2*k+1] % mod;
					v[j + k * bsz] = (a + b) % mod;
					v[j + k * bsz + v.size()/2] = (a - b + mod) % mod;
					cur = (cur * ang) % mod;
				}
			}
		}
		if(inv){
			lint mul = ipow(v.size(), mod-2);
			for(int i=0; i<v.size(); i++){
				v[i] = (mul * v[i]) % mod;
			}
		}
	}
	vector<int> multiply(vector<int> a, vector<int> b){
		int w = 1;
		while(w < max(a.size(), b.size())) w <<= 1;
		w <<= 1;
		a.resize(w);
		b.resize(w);
		fft(a, 0); 
		fft(b, 0);
		for(int i=0; i<w; i++) a[i] = (1ll * a[i] * b[i]) % mod;
		fft(a, 1);
		return a;
	}
}
