const int mod = 1e9 + 7;

lint ipow(lint x, lint p){
	lint ret = 1, piv = x % mod;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret % mod;
}

const int MAXN = 105;
struct matrix{
	lint adj[MAXN][MAXN];
	int n;
	matrix(int _n, int c){
		n = _n;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				adj[i][j] = (i == j ? c : 0);
			}
		}
	}
	matrix operator*(const matrix &a)const{
		matrix c(n, 0);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					c.adj[j][k] += adj[j][i] * a.adj[i][k] % mod;
					c.adj[j][k] %= mod;
				}
			}
		}
		return c;
	}
	matrix operator+(const matrix &a)const{
		matrix c(n, 0);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				c.adj[i][j] = (adj[i][j] + a.adj[i][j]) % mod;
			}
		}
		return c;
	}
	matrix operator-(const matrix &a)const{
		matrix c(n, 0);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				c.adj[i][j] = (adj[i][j] + mod - a.adj[i][j]) % mod;
			}
		}
		return c;
	}
};

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

namespace miller_rabin{
	lint mul(lint a, lint b, lint p){
		lint ret = 0;
		while(a){
			if(a&1) ret = (ret + b) % p;
			a >>= 1;
			b = (b << 1) % p;
		}
		return ret;
	}
	lint ipow(lint x, lint y, lint p){
		lint ret = 1, piv = x % p;
		while(y){
			if(y&1) ret = mul(ret, piv, p);
			piv = mul(piv, piv, p);
			y >>= 1;
		}
		return ret;
	}
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
		if(x < 40) return 0;
		return 1;
	}
}

namespace count_digits{
	const int MAXN = 17;
	vector<lint> solve(lint b){
		lint pw[MAXN+1];
		pw[0] = 1;
		for(int i=1; i<=MAXN; i++) pw[i] = pw[i-1] * 10;
		vector<lint> ret(10);
		for(int i=0; i<MAXN; i++){
			ret[0] += max(b - pw[i] + 1, 0ll);
		}
		for(int i=1; i<=9; i++){
			for(int j=0; i * pw[j] <= b; j++){
				lint piv = i * pw[j];
				ret[i] += ((b - i * pw[j] + 1) / pw[j+1]) * pw[j];
				ret[i] += min((b - i * pw[j] + 1) % pw[j+1], pw[j]);
			}
			ret[0] -= ret[i];
		}
		return ret;
	}
};

const int MAXN = 1000005;
struct count_primes{  
	// code from https://github.com/stjepang/snippets/blob/master/count_primes.cpp
	//
	// Time complexity: No idea. Primes up to 10^12 can be counted in ~1 second.
	//
	// Constants to configure:
	// - MAX is the maximum value of sqrt(N) + 2

	bool prime[MAXN];
	int prec[MAXN];
	vector<int> P;

	void init() {
		prime[2] = true;
		for (int i = 3; i < MAX; i += 2){
			prime[i] = true;
		}
		for (int i = 3; i*i < MAX; i += 2){
			if (prime[i]){
				for (int j = i*i; j < MAX; j += i+i)
					prime[j] = false;
			}
		}
		for(int i=1; i<MAX; i++){
			if (prime[i]) P.push_back(i);
			prec[i] = prec[i-1] + prime[i];
		}
	}

	lint rec(llint N, int K) {
		if (N <= 1 || K < 0) return 0;
		if (N <= P[K]) return N-1;
		if (N < MAX && 1ll * P[K]*P[K] > N) return N-1 - prec[N] + prec[P[K]];

		const int LIM = 250;
		static int memo[LIM*LIM][LIM];

		bool ok = N < LIM*LIM;
		if (ok && memo[N][K]) return memo[N][K];

		lint ret = N/P[K] - rec(N/P[K], K-1) + rec(N, K-1);

		if (ok) memo[N][K] = ret;
		return ret;
	}

	llint count_primes(llint N) {
		if (N < MAX) return prec[N];
		int K = prec[(int)sqrt(N) + 1];
		return N-1 - rec(N, K) + prec[P[K]];
	}
}count_primes;
