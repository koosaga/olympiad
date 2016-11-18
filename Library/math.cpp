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
		vector<base> w(v.size());
		for(int i=2; i<=v.size(); i<<=1){
			int bsz = v.size() / i;
			base ang(cos(2 * M_PI / i), sin(2 * M_PI / i));
			if(inv) ang = base(1, 0) / ang;
			for(int j=0; j<bsz; j++){
				for(int k=0; k<i; k++){
					w[k] = v[bsz * k + j];
				}
				base pw(1, 0);
				for(int k=0; k<i/2; k++){
					base a = w[2*k], b = w[2*k+1] * pw;
					v[bsz * k + j] = a + b;
					v[bsz * k + j + v.size()/2] = a - b;
					pw *= ang;
				}
			}
		}
		if(inv){
			for(int i=0; i<v.size(); i++){
				v[i] /= v.size();
			}
		}
	}
	vector<int> multiply(vector<int> &v, vector<int> &w){
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
		vector<int> ret(n);
		for(int i=0; i<n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
	vector<int> power(vector<int> &v){
		vector<base> fv(v.begin(), v.end());
		int n = 1;
		while(n < v.size()) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fft(fv, 0);
		for(int i=0; i<n; i++) fv[i] *= fv[i];
		fft(fv, 1);
		vector<int> ret(n);
		for(int i=0; i<n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
};

struct miller_rabin{
	lint mul(lint a, lint b, lint p){
		lint ret = 0;
		while(b){
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
}isprime;

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
