lint gcd(lint x, lint y){ return y ? gcd(y, x%y) : x; }

namespace miller_rabin{
	lint mul(lint a, lint b, lint p){
		a %= p, b %= p;
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
	bool isprime(lint n){
		for(auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
			if(x > 40 && miller_rabin(n, i)) return 0;
			if(x == i) return 1;
		}
		if(x <= 40) return 0;
		return 1;
	}
}
namespace pollard_rho{
	lint f(lint x, lint n, lint c){
		return (c + miller_rabin::mul(x, x, n)) % n;
	}
	void rec(lint n, vector<lint> &v){
		if(n == 1) return;
		if(n % 2 == 0){
			v.push_back(2);
			rec(n/2, v);
			return;
		}
		if(miller_rabin::isprime(n)){
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
};

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
