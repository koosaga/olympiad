const int mod = 1e9 + 7;

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
	void init(int _n, int c){
		n = _n;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				adj[i][j] = (i == j ? c : 0);
			}
		}
	}
	matrix operator*(const mat &a)const{
		matrix c;
		c.init();
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
};
