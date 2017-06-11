namespace fft{
	typedef complex<double> base;
	void fft(vector<base> &v, bool inv){
		int n = v.size();
		vector<base> w(n/2), aux(n);
		for(int i=0; i<n/2; i++){
			int k = i&-i;
			if(i == k){
				double ang = 2 * M_PI * i / n;
				if(inv) ang *= -1;
				w[i] = base(cos(ang), sin(ang));
			}
			else w[i] = w[i-k] * w[k];
		}
		for(int i=n/2; i; i>>=1){
			aux = v;
			for(int k=0; 2*k<n; k+=i){
				for(int j=0; j<i; j++){
					base a = aux[2*k + j], b = aux[2*k + j + i] * w[k];
					v[k + j] = a + b;
					v[k + j + n/2] = a - b;
				}
			}
		}
		if(inv){
			for(int i=0; i<n; i++){
				v[i] /= n;
			}
		}
	}
	vector<lint> multiply(vector<lint> &v, vector<lint> &w){
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fw.resize(n);
		fft(fv, 0);
		fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
	vector<lint> multiply(vector<lint> &v, vector<lint> &w, int b){
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		vector<base> v1(n), v2(n), v3(n), v4(n), r1(n), r2(n), r3(n);
		for(int i=0; i<v.size(); i++){
			v1[i] = base(v[i] / b, 0);
			v2[i] = base(v[i] % b, 0);
		}
		for(int i=0; i<w.size(); i++){
			v3[i] = base(w[i] / b, 0);
			v4[i] = base(w[i] % b, 0);
		}
		fft(v1, 0);
		fft(v2, 0);
		fft(v3, 0);
		fft(v4, 0);
		for(int i=0; i<n; i++){
			r1[i] = v1[i] * v3[i];
			r2[i] = v1[i] * v4[i] + v2[i] * v3[i];
			r3[i] = v2[i] * v4[i];
		}
		fft(r1, 1);
		fft(r2, 1);
		fft(r3, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++){
			ret[i] = (lint)round(r1[i].real()) * b * b + (lint)round(r2[i].real()) * b + (lint)round(r3[i].real());
		}
		return ret;
	}
}

